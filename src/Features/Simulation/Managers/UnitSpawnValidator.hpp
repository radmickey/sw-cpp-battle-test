#pragma once

#include "Core/Map/IPosition.hpp"
#include "Core/Simulation/Managers/IUnitSpawnValidator.hpp"

#include <memory>

namespace sw::core
{
	class Unit;
	class IUnitManager;
	class IMap;
}

namespace sw::features
{
	class UnitSpawnValidator : public sw::core::IUnitSpawnValidator
	{
	private:
		sw::core::IMap* map;
		sw::core::IUnitManager* unitManager;

	public:
		UnitSpawnValidator() :
				map(nullptr),
				unitManager(nullptr)
		{}

		void setMap(sw::core::IMap* map) override
		{
			this->map = map;
		}

		void setUnitManager(sw::core::IUnitManager* unitManager) override
		{
			this->unitManager = unitManager;
		}

		void validateUnitSpawn(const sw::core::Unit& unit) const override;
		void validateUnitPosition(const sw::core::IPosition& pos, bool occupiesCell) const override;
	};
}
