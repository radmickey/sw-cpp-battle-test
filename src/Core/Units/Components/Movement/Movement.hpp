#pragma once

#include "Core/Map/Position.hpp"
#include "IMovementRuleService.hpp"

#include <memory>
#include <optional>
#include <vector>

namespace sw::core
{
	class IMap;
}

namespace sw::core
{
	class Movement
	{
	private:
		Position position;
		std::optional<Position> targetPosition;
		bool canMoveFlag;
		bool isFlyingFlag;
		bool occupiesCellFlag;
		std::unique_ptr<IMovementRuleService> movementRule;

	public:
		Movement(
			Position pos,
			std::unique_ptr<IMovementRuleService> rule,
			bool canMove,
			bool isFlying = false,
			bool occupiesCell = true);

		Position getPosition() const;
		std::optional<Position> getTargetPosition() const;
		bool canMove() const;
		bool isFlying() const;
		bool occupiesCell() const;

		void setPosition(Position pos);
		void setTargetPosition(Position target);
		void clearTargetPosition();
		void setMovementRule(std::unique_ptr<IMovementRuleService> rule);

		bool isTargetReached() const;
		bool hasTarget() const;
		std::optional<Position> calculateNextPosition(const IMap& map, uint32_t moveDistance, bool needsFreeCell) const;
	};
}
