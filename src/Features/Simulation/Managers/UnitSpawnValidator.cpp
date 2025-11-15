#include "UnitSpawnValidator.hpp"

#include "Core/Map/IMap.hpp"
#include "Core/Simulation/Managers/IUnitManager.hpp"
#include "Core/Units/Unit.hpp"

#include <stdexcept>

namespace sw::features
{

	void UnitSpawnValidator::validateUnitSpawn(const sw::core::Unit& unit) const
	{
		if (!map)
		{
			throw std::runtime_error("Map not created");
		}

		if (unitManager && unitManager->getUnit(unit.getId()))
		{
			throw std::runtime_error("Unit with ID " + std::to_string(unit.getId()) + " already exists");
		}
	}

	void UnitSpawnValidator::validateUnitPosition(const sw::core::IPosition& pos, bool occupiesCell) const
	{
		if (!map->isValid(pos))
		{
			throw std::runtime_error("Position out of bounds");
		}

		if (occupiesCell && map->isOccupied(pos))
		{
			throw std::runtime_error("Cell already occupied");
		}
	}
}
