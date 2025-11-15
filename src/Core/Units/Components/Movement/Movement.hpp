#pragma once

#include "Core/Map/IPosition.hpp"
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
		std::unique_ptr<IPosition> position;
		std::unique_ptr<IPosition> targetPosition;
		bool canMoveFlag;
		bool isFlyingFlag;
		bool occupiesCellFlag;
		std::unique_ptr<IMovementRuleService> movementRule;

	public:
		Movement(
			std::unique_ptr<IPosition> pos,
			std::unique_ptr<IMovementRuleService> rule,
			bool canMove,
			bool isFlying = false,
			bool occupiesCell = true);

		const IPosition& getPosition() const;
		const IPosition* getTargetPosition() const;
		bool canMove() const;
		bool isFlying() const;
		bool occupiesCell() const;

		void setPosition(std::unique_ptr<IPosition> pos);
		void setTargetPosition(std::unique_ptr<IPosition> target);
		void clearTargetPosition();
		void setMovementRule(std::unique_ptr<IMovementRuleService> rule);

		bool isTargetReached() const;
		bool hasTarget() const;
		std::unique_ptr<IPosition> calculateNextPosition(const IMap& map, uint32_t moveDistance, bool needsFreeCell) const;
	};
}
