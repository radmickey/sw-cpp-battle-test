#include "Movement.hpp"

#include "Core/Map/IMap.hpp"

namespace sw::core
{
	Movement::Movement(
		Position pos, std::unique_ptr<IMovementRuleService> rule, bool canMove, bool isFlying, bool occupiesCell) :
			position(pos),
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
		return targetPosition.has_value();
	}

	Position Movement::getPosition() const
	{
		return position;
	}

	std::optional<Position> Movement::getTargetPosition() const
	{
		return targetPosition;
	}

	void Movement::setPosition(Position pos)
	{
		position = pos;
	}

	void Movement::setTargetPosition(Position target)
	{
		targetPosition = target;
	}

	void Movement::clearTargetPosition()
	{
		targetPosition = std::nullopt;
	}

	void Movement::setMovementRule(std::unique_ptr<IMovementRuleService> rule)
	{
		movementRule = std::move(rule);
	}

	bool Movement::isTargetReached() const
	{
		if (!targetPosition.has_value())
		{
			return false;
		}
		return position == *targetPosition;
	}

	std::optional<Position> Movement::calculateNextPosition(
		const IMap& map, uint32_t moveDistance, bool needsFreeCell) const
	{
		if (!targetPosition.has_value() || isTargetReached() || !movementRule)
		{
			return std::nullopt;
		}

		auto reachablePositions = movementRule->collectReachablePositions(position, map, moveDistance, needsFreeCell);
		Position bestPos = movementRule->findBestPosition(reachablePositions, position, targetPosition);

		if (bestPos != position)
		{
			return bestPos;
		}

		return std::nullopt;
	}
}
