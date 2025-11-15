#include "Move.hpp"

#include "Core/Battle/Actions/ActionContext.hpp"
#include "Core/Map/IMap.hpp"
#include "Core/Simulation/IEventLogger.hpp"
#include "Core/Units/Unit.hpp"

namespace sw::features
{
	using sw::core::ActionCheckContext;
	using sw::core::ActionContext;
	using sw::core::IEventLogger;
	using sw::core::IMap;
	using sw::core::IPosition;
	using sw::core::Unit;

	Move::Move(uint32_t moveDistance) :
			moveDistance(moveDistance)
	{}

	bool Move::canExecute(const sw::core::Unit& actor, const sw::core::ActionCheckContext& context)
	{
		if (!actor.canMove())
		{
			return false;
		}

		const IPosition* targetPos = actor.getTargetPosition();
		if (!targetPos)
		{
			return false;
		}

		const IPosition& currentPos = actor.getPosition();
		return currentPos != *targetPos;
	}

	void Move::updateUnitPosition(
		sw::core::Unit& actor,
		sw::core::IMap& map,
		const IPosition& newPos,
		const IPosition& oldPos,
		sw::core::IEventLogger& logger,
		uint64_t currentTick) const
	{
		if (actor.occupiesCell())
		{
			map.free(oldPos, actor.getId());
			map.occupy(newPos, actor.getId());
		}

		actor.setPosition(newPos.clone());
		logger.logUnitMoved(actor.getId(), newPos, currentTick);
	}

	void Move::endMarch(
		sw::core::Unit& actor, const IPosition& pos, sw::core::IEventLogger& logger, uint64_t currentTick) const
	{
		logger.logMarchEnded(actor.getId(), pos, currentTick);
		actor.clearTargetPosition();
	}

	void Move::execute(sw::core::Unit& actor, sw::core::ActionContext& context)
	{
		const IPosition* targetPos = actor.getTargetPosition();
		if (!targetPos)
		{
			return;
		}

		const IPosition& currentPos = actor.getPosition();

		if (currentPos == *targetPos)
		{
			endMarch(actor, currentPos, context.logger, context.currentTick);
			return;
		}

		auto nextPos = actor.getMovement().calculateNextPosition(context.map, moveDistance, actor.occupiesCell());
		if (nextPos)
		{
			updateUnitPosition(actor, context.map, *nextPos, currentPos, context.logger, context.currentTick);

			if (*nextPos == *targetPos)
			{
				endMarch(actor, *nextPos, context.logger, context.currentTick);
			}
		}
	}
}
