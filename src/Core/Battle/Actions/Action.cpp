#include "Action.hpp"

#include "ActionContext.hpp"
#include "Core/Simulation/IEventLogger.hpp"
#include "Core/Units/Unit.hpp"
#include "Core/Units/UnitId.hpp"

namespace sw::core
{
	void Action::performAttack(Unit& actor, Unit* target, int damage, IEventLogger& logger, uint64_t currentTick)
	{
		target->takeDamage(damage);
		int targetHpAfter = target->getHp();

		logger.logUnitAttacked(
			actor.getId(),
			target->getId(),
			static_cast<uint32_t>(damage),
			static_cast<uint32_t>(targetHpAfter),
			currentTick);

		if (target->shouldBeRemoved())
		{
			logger.logUnitDied(target->getId(), currentTick);
		}
	}
}
