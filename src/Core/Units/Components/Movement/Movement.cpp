#include "Movement.hpp"

#include "Core/Map/IMap.hpp"

namespace sw::core
{
	Movement::Movement(
		std::unique_ptr<IPosition> pos, std::unique_ptr<IMovementRuleService> rule, bool canMove, bool isFlying, bool occupiesCell) :
			position(std::move(pos)),
			canMoveFlag(canMove),
			isFlyingFlag(isFlying),
			occupiesCellFlag(occupiesCell),
			movementRule(std::move(rule))
	{}

	bool Movement::canMove() const
	{
		return canMoveFlag;
	}

	bool Movement::isFlying() const
	{
		return isFlyingFlag;
	}

	bool Movement::occupiesCell() const
	{
		return occupiesCellFlag;
	}

	bool Movement::hasTarget() const
	{
		return targetPosition != nullptr;
	}

	const IPosition& Movement::getPosition() const
	{
		return *position;
	}

	const IPosition* Movement::getTargetPosition() const
	{
		return targetPosition.get();
	}

	void Movement::setPosition(std::unique_ptr<IPosition> pos)
	{
		position = std::move(pos);
	}

	void Movement::setTargetPosition(std::unique_ptr<IPosition> target)
	{
		targetPosition = std::move(target);
	}

	void Movement::clearTargetPosition()
	{
		targetPosition.reset();
	}

	void Movement::setMovementRule(std::unique_ptr<IMovementRuleService> rule)
	{
		movementRule = std::move(rule);
	}

	bool Movement::isTargetReached() const
	{
		if (!targetPosition)
		{
			return false;
		}
		return *position == *targetPosition;
	}

	std::unique_ptr<IPosition> Movement::calculateNextPosition(
		const IMap& map, uint32_t moveDistance, bool needsFreeCell) const
	{
		if (!targetPosition || isTargetReached() || !movementRule)
		{
			return nullptr;
		}

		auto reachablePositions = movementRule->collectReachablePositions(*position, map, moveDistance, needsFreeCell);
		auto bestPos = movementRule->findBestPosition(reachablePositions, *position, targetPosition.get());

		if (bestPos && *bestPos != *position)
		{
			return bestPos;
		}

		return nullptr;
	}
}
