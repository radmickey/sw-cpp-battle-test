#pragma once

#include "Core/Simulation/Managers/IGameContinuationChecker.hpp"

namespace sw::core
{
	class IUnitManager;
	class IActionAvailabilityChecker;
}

namespace sw::features
{
	class GameContinuationChecker : public sw::core::IGameContinuationChecker
	{
	private:
		sw::core::IUnitManager* unitManager;
		sw::core::IActionAvailabilityChecker* actionChecker;

	public:
		GameContinuationChecker(
			sw::core::IUnitManager* unitManager, sw::core::IActionAvailabilityChecker* actionChecker);

		bool shouldContinue() const override;
	};
}
