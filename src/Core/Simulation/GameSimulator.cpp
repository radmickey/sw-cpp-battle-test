#include "GameSimulator.hpp"

#include "Core/Battle/Actions/ActionContext.hpp"
#include "Core/Map/IMap.hpp"
#include "Core/Map/IPosition.hpp"
#include "Core/Units/Unit.hpp"
#include "GameTime.hpp"
#include "IEventLogger.hpp"

#include <stdexcept>

namespace sw::core
{
	GameSimulator::GameSimulator(
		IEventLogger& eventLogger, GameTime& gameTime, std::unique_ptr<IGameContinuationChecker> continuationChecker) :
			eventLogger(&eventLogger),
			gameTime(gameTime),
			rng(std::random_device{}()),
			continuationChecker(std::move(continuationChecker))
	{}

	GameSimulator::~GameSimulator() = default;

	void GameSimulator::createMap(
		const std::vector<uint32_t>& dimensionSizes,
		std::unique_ptr<IUnitManager> unitManager,
		std::unique_ptr<IMapManager> mapManager,
		std::unique_ptr<IUnitSpawnValidator> spawnValidator)
	{
		this->mapManager = std::move(mapManager);
		this->mapManager->createMap(dimensionSizes);
		this->unitManager = std::move(unitManager);
		this->unitManager->setMap(this->mapManager->getMap());
		this->spawnValidator = std::move(spawnValidator);
		this->spawnValidator->setMap(this->mapManager->getMap());
		this->spawnValidator->setUnitManager(this->unitManager.get());
		cachedActionContext.reset();
	}

	void GameSimulator::setContinuationChecker(std::unique_ptr<IGameContinuationChecker> continuationChecker)
	{
		this->continuationChecker = std::move(continuationChecker);
	}

	void GameSimulator::spawnUnit(std::unique_ptr<Unit> unit)
	{
		spawnValidator->validateUnitSpawn(*unit);

		const IPosition& pos = unit->getPosition();
		bool occupiesCell = unit->occupiesCell();
		spawnValidator->validateUnitPosition(pos, occupiesCell);

		if (occupiesCell)
		{
			mapManager->getMap()->occupy(pos, unit->getId());
		}

		unitManager->addUnit(std::move(unit));
	}

	Unit* GameSimulator::getUnit(UnitId id) const
	{
		return unitManager ? unitManager->getUnit(id) : nullptr;
	}

	ActionContext& GameSimulator::getActionContext()
	{
		if (!cachedActionContext)
		{
			auto getUnitFunc = unitManager->getUnitFunction();
			auto getUnitsInRadiusFunc = unitManager->getUnitsInRadiusFunction();
			cachedActionContext.emplace(
				*mapManager->getMap(), *eventLogger, rng, gameTime.getCurrentTick(), getUnitFunc, getUnitsInRadiusFunc);
		}
		else
		{
			cachedActionContext->currentTick = gameTime.getCurrentTick();
		}
		return *cachedActionContext;
	}

	void GameSimulator::setUnitTargetPosition(UnitId id, std::unique_ptr<IPosition> target)
	{
		Unit* unit = getUnit(id);
		if (!unit)
		{
			throw std::runtime_error("Unit not found: " + std::to_string(id));
		}
		unit->setTargetPosition(std::move(target));
	}

	bool GameSimulator::shouldContinue()
	{
		return continuationChecker && continuationChecker->shouldContinue();
	}

	void GameSimulator::processTick()
	{
		gameTime.nextTick();

		ActionContext& context = getActionContext();

		if (unitManager)
		{
			for (const auto& unit : unitManager->getUnits())
			{
				if (unit->hasActions())
				{
					unit->act(context);
				}
			}

			unitManager->removeDeadUnits();
		}
	}

	void GameSimulator::simulate()
	{
		if (!mapManager || !mapManager->hasMap())
		{
			throw std::runtime_error("Map not created");
		}

		while (shouldContinue())
		{
			processTick();
		}
	}
}
