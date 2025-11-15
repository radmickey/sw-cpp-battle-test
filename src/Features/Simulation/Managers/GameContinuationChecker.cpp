#include "GameContinuationChecker.hpp"

#include "Core/Simulation/Managers/IActionAvailabilityChecker.hpp"
#include "Core/Simulation/Managers/IUnitManager.hpp"
#include "Core/Units/Unit.hpp"

namespace sw::features
{
	GameContinuationChecker::GameContinuationChecker(
		sw::core::IUnitManager* unitManager, sw::core::IActionAvailabilityChecker* actionChecker) :
			unitManager(unitManager),
			actionChecker(actionChecker)
	{}

	bool GameContinuationChecker::shouldContinue() const
	{
		if (!unitManager || !actionChecker)
		{
			return false;
		}

		int aliveCount = 0;
		int canActCount = 0;

		for (const auto& unit : unitManager->getUnits())
		{
			if (unit->isAlive())
			{
				aliveCount++;
				if (actionChecker->hasAvailableAction(*unit))
				{
					canActCount++;
				}
			}
		}

		return canActCount > 0 && aliveCount > 1;
	}
}
