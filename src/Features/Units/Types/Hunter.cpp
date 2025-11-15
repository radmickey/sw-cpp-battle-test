#include "Hunter.hpp"

namespace sw::features
{
	Hunter::Hunter(sw::core::UnitId id, sw::core::Position pos, int hp, int agility, int strength, int range) :
			Unit(
				id,
				pos,
				std::make_unique<LifecycleService>(),
				std::make_unique<MovementRuleService>(),
				std::make_unique<ActionExecutorService>(),
				sw::core::UnitProperties{true, true, false, true, hp}),
			agility(agility),
			strength(strength),
			range(range)
	{}

	void Hunter::initializeActions()
	{
		addAction(std::make_unique<sw::features::RangedAttack>(2, range, agility, true));
		addAction(std::make_unique<sw::features::MeleeAttack>(strength));
		addAction(std::make_unique<sw::features::Move>());
	}
}
