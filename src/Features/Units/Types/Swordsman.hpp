#pragma once

#include "Features/Map/Position2D.hpp"
#include "Core/Units/Unit.hpp"
#include "Core/Units/UnitId.hpp"
#include "Features/Battle/Actions/MeleeAttack.hpp"
#include "Features/Battle/Actions/Move.hpp"
#include "Features/Battle/Combat/ActionExecutorService.hpp"
#include "Features/Units/Services/LifecycleService.hpp"
#include "Features/Units/Services/MovementRuleService.hpp"

#include <memory>

namespace sw::features
{
	class Swordsman : public sw::core::Unit
	{
	private:
		int strength;

	public:
		Swordsman(sw::core::UnitId id, sw::features::Position2D pos, int hp, int strength);

		void initializeActions() override;
	};
}
