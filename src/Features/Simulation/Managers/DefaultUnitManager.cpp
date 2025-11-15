#include "DefaultUnitManager.hpp"

#include "Features/Map/DistanceCalculators/ChebyshevDistanceCalculator.hpp"

#include <algorithm>

namespace sw::features
{
	DefaultUnitManager::DefaultUnitManager() :
			map(nullptr)
	{}

	void DefaultUnitManager::setMap(sw::core::IMap* map)
	{
		this->map = map;
	}

	void DefaultUnitManager::addUnit(std::unique_ptr<sw::core::Unit> unit)
	{
		units.push_back(std::move(unit));
	}

	sw::core::Unit* DefaultUnitManager::getUnit(sw::core::UnitId id) const
	{
		auto it = std::find_if(
			units.begin(),
			units.end(),
			[id](const std::unique_ptr<sw::core::Unit>& unit) { return unit->getId() == id; });
		return (it != units.end()) ? it->get() : nullptr;
	}

	void DefaultUnitManager::removeDeadUnits()
	{
		units.erase(
			std::remove_if(
				units.begin(),
				units.end(),
				[this](std::unique_ptr<sw::core::Unit>& unit)
				{
					if (unit->shouldBeRemoved())
					{
						if (unit->occupiesCell() && map)
						{
							map->free(unit->getPosition(), unit->getId());
						}
						return true;
					}
					return false;
				}),
			units.end());
	}

	std::vector<sw::core::Unit*> DefaultUnitManager::getUnitsInRadius(
		const sw::core::IPosition& center, uint32_t radius) const
	{
		std::vector<sw::core::Unit*> result;
		sw::features::ChebyshevDistanceCalculator calculator;
		for (const auto& unit : units)
		{
			if (!unit->isAlive())
			{
				continue;
			}
			const sw::core::IPosition& unitPos = unit->getPosition();
			uint32_t distance = calculator.calculate(center, unitPos);
			if (distance <= radius)
			{
				result.push_back(unit.get());
			}
		}
		return result;
	}

	std::function<sw::core::Unit*(sw::core::UnitId)> DefaultUnitManager::getUnitFunction() const
	{
		return [this](sw::core::UnitId id) -> sw::core::Unit*
		{
			return getUnit(id);
		};
	}

	std::function<std::vector<sw::core::Unit*>(const sw::core::IPosition&, uint32_t)>
	DefaultUnitManager::getUnitsInRadiusFunction() const
	{
		return [this](const sw::core::IPosition& center, uint32_t radius) -> std::vector<sw::core::Unit*>
		{
			return getUnitsInRadius(center, radius);
		};
	}

	const std::vector<std::unique_ptr<sw::core::Unit>>& DefaultUnitManager::getUnits() const
	{
		return units;
	}
}
