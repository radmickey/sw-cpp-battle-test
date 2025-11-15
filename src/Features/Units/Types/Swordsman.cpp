#include "Swordsman.hpp"

#include "Features/Battle/Actions/DefaultActionManager.hpp"
#include "Features/Units/Components/Health/DefaultHealth.hpp"

namespace sw::features
{
	Swordsman::Swordsman(sw::core::UnitId id, sw::features::Position2D pos, int hp, int strength) :
			Unit(
				id,
				std::make_unique<Position2D>(pos),
				std::make_unique<DefaultHealth>(true, hp),
				std::make_unique<DefaultActionManager>(),
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
