#pragma once

#include "Core/Map/IPosition.hpp"
#include "Core/Units/UnitId.hpp"

#include <functional>
#include <memory>
#include <vector>

namespace sw::core
{
	class Unit;
	class IMap;
}

namespace sw::core
{
	class IUnitManager
	{
	public:
		virtual ~IUnitManager() = default;

		virtual void setMap(IMap* map) = 0;
		virtual void addUnit(std::unique_ptr<Unit> unit) = 0;
		virtual Unit* getUnit(UnitId id) const = 0;
		virtual void removeDeadUnits() = 0;
		virtual std::vector<Unit*> getUnitsInRadius(const IPosition& center, uint32_t radius) const = 0;
		virtual std::function<Unit*(UnitId)> getUnitFunction() const = 0;
		virtual std::function<std::vector<Unit*>(const IPosition&, uint32_t)> getUnitsInRadiusFunction() const = 0;
		virtual const std::vector<std::unique_ptr<Unit>>& getUnits() const = 0;
	};
}
