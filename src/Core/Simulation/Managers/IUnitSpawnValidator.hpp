#pragma once

#include "Core/Map/IPosition.hpp"

#include <memory>

namespace sw::core
{
	class Unit;
	class IMap;
	class IUnitManager;
}

namespace sw::core
{
	class IUnitSpawnValidator
	{
	public:
		virtual ~IUnitSpawnValidator() = default;

		virtual void setMap(IMap* map) = 0;
		virtual void setUnitManager(IUnitManager* unitManager) = 0;
		virtual void validateUnitSpawn(const Unit& unit) const = 0;
		virtual void validateUnitPosition(const IPosition& pos, bool occupiesCell) const = 0;
	};
}
