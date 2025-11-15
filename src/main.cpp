#include "Features/Map/Position2D.hpp"
#include "Core/Simulation/GameSimulator.hpp"
#include "Core/Simulation/GameTime.hpp"
#include "Core/Units/UnitFactory.hpp"
#include "Features/Simulation/Managers/ActionAvailabilityChecker.hpp"
#include "Features/Simulation/Managers/DefaultUnitManager.hpp"
#include "Features/Simulation/Managers/GameContinuationChecker.hpp"
#include "Features/Simulation/Managers/MapManager.hpp"
#include "Features/Simulation/Managers/UnitSpawnValidator.hpp"
#include "Features/Units/Types/Hunter.hpp"
#include "Features/Units/Types/Swordsman.hpp"
#include "IO/Commands/CreateMap.hpp"
#include "IO/Commands/March.hpp"
#include "IO/Commands/SpawnHunter.hpp"
#include "IO/Commands/SpawnSwordsman.hpp"
#include "IO/Events/MapCreated.hpp"
#include "IO/Events/MarchEnded.hpp"
#include "IO/Events/MarchStarted.hpp"
#include "IO/Events/UnitAttacked.hpp"
#include "IO/Events/UnitDied.hpp"
#include "IO/Events/UnitMoved.hpp"
#include "IO/Events/UnitSpawned.hpp"
#include "IO/System/CommandParser.hpp"
#include "IO/System/EventLog.hpp"
#include "IO/System/EventLogAdapter.hpp"

#include <fstream>
#include <iostream>

int main(int argc, char** argv)
{
	using namespace sw;

	if (argc != 2)
	{
		std::cerr << "Error: No file specified in command line argument\n";
		std::cerr << "Usage: " << (argc > 0 ? argv[0] : "sw_battle_test") << " <commands_file>\n";
		return 1;
	}

	std::ifstream file(argv[1]);
	if (!file)
	{
		std::cerr << "Error: File not found - " << argv[1] << "\n";
		return 1;
	}

	sw::EventLog eventLog;
	io::EventLogAdapter eventLogger(eventLog);
	core::GameSimulator simulator(eventLogger, core::GameTime::getMutableInstance());
	core::UnitFactory factory;

	std::unique_ptr<features::ActionAvailabilityChecker> actionChecker;

	io::CommandParser parser;
	uint64_t commandTick = 1;

	auto spawnUnit = [&](auto unit, const std::string& unitType, uint32_t unitId, uint32_t x, uint32_t y)
	{
		simulator.spawnUnit(std::move(unit));
		eventLog.log(commandTick, io::UnitSpawned{unitId, unitType, x, y});
	};

	parser.add<io::CreateMap>(
		[&](auto command)
		{
			auto unitManager = std::make_unique<features::DefaultUnitManager>();
			auto mapManager = std::make_unique<features::MapManager>();
			auto spawnValidator = std::make_unique<features::UnitSpawnValidator>();

			auto unitManagerPtr = unitManager.get();
			auto mapManagerPtr = mapManager.get();

		simulator.createMap(
			{command.width, command.height},
			std::move(unitManager),
			std::move(mapManager),
			std::move(spawnValidator));

			actionChecker
				= std::make_unique<features::ActionAvailabilityChecker>(mapManagerPtr->getMap(), unitManagerPtr);

			simulator.setContinuationChecker(
				std::make_unique<features::GameContinuationChecker>(unitManagerPtr, actionChecker.get()));

			eventLog.log(commandTick, io::MapCreated{command.width, command.height});
		});

	parser.add<io::SpawnSwordsman>(
		[&](auto command)
		{
		auto unit = factory.create<features::Swordsman>(
			command.unitId, features::Position2D{command.x, command.y}, command.hp, command.strength);
			spawnUnit(std::move(unit), "Swordsman", command.unitId, command.x, command.y);
		});

	parser.add<io::SpawnHunter>(
		[&](auto command)
		{
		auto unit = factory.create<features::Hunter>(
			command.unitId,
			features::Position2D{command.x, command.y},
			command.hp,
			command.agility,
			command.strength,
			command.range);
			spawnUnit(std::move(unit), "Hunter", command.unitId, command.x, command.y);
		});

	parser.add<io::March>(
		[&](auto command)
		{
		auto unit = simulator.getUnit(command.unitId);
		if (!unit)
		{
			throw std::runtime_error("Unit not found: " + std::to_string(command.unitId));
		}
		const core::IPosition& currentPos = unit->getPosition();
		simulator.setUnitTargetPosition(command.unitId, std::make_unique<features::Position2D>(command.targetX, command.targetY));
		eventLog.log(
			commandTick,
			io::MarchStarted{command.unitId, currentPos.getCoordinate(0), currentPos.getCoordinate(1), command.targetX, command.targetY});
		});

	try
	{
		parser.parse(file);
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error parsing commands: " << e.what() << "\n";
		return 1;
	}

	try
	{
		simulator.simulate();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error during simulation: " << e.what() << "\n";
		return 1;
	}

	return 0;
}
