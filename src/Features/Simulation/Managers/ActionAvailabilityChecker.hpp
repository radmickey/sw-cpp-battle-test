#pragma once

#include "Core/Simulation/Managers/IActionAvailabilityChecker.hpp"

namespace sw::core
{
	class Unit;
	class IMap;
	class IUnitManager;
}

namespace sw::features
{
	class ActionAvailabilityChecker : public sw::core::IActionAvailabilityChecker
	{
	private:
		sw::core::IMap* map;
		sw::core::IUnitManager* unitManager;

	public:
		ActionAvailabilityChecker(sw::core::IMap* map, sw::core::IUnitManager* unitManager);

		bool hasAvailableAction(const sw::core::Unit& unit) const override;
	};
}
