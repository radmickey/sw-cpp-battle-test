#include "ActionAvailabilityChecker.hpp"

#include "Core/Battle/Actions/ActionContext.hpp"
#include "Core/Map/IMap.hpp"
#include "Core/Simulation/Managers/IUnitManager.hpp"
#include "Core/Units/Unit.hpp"

namespace sw::features
{
	ActionAvailabilityChecker::ActionAvailabilityChecker(sw::core::IMap* map, sw::core::IUnitManager* unitManager) :
			map(map),
			unitManager(unitManager)
	{}

	bool ActionAvailabilityChecker::hasAvailableAction(const sw::core::Unit& unit) const
	{
		if (!unit.canAct())
		{
			return false;
		}

		auto getUnitFunc = unitManager->getUnitFunction();
		auto getUnitsInRadiusFunc = unitManager->getUnitsInRadiusFunction();
		sw::core::ActionCheckContext checkContext(*map, getUnitFunc, getUnitsInRadiusFunc);
		for (const auto& action : unit.getActions())
		{
			if (action->canExecute(unit, checkContext))
			{
				return true;
			}
		}
		return false;
	}
}
