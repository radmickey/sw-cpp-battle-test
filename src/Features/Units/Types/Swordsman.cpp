#include "Swordsman.hpp"

namespace sw::features
{
	Swordsman::Swordsman(sw::core::UnitId id, sw::core::Position pos, int hp, int strength) :
			Unit(
				id,
				pos,
				std::make_unique<LifecycleService>(),
				std::make_unique<MovementRuleService>(),
				std::make_unique<ActionExecutorService>(),
				sw::core::UnitProperties{true, true, false, true, hp}),
			strength(strength)
	{}

	void Swordsman::initializeActions()
	{
		addAction(std::make_unique<sw::features::MeleeAttack>(strength));
		addAction(std::make_unique<sw::features::Move>());
	}
}
