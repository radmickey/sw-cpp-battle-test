#pragma once

#include "Components/Health/IHealth.hpp"
#include "Components/Movement/Movement.hpp"
#include "Core/Battle/Actions/IAction.hpp"
#include "Core/Battle/Actions/IActionManager.hpp"
#include "Core/Battle/Combat/IActionExecutorService.hpp"
#include "Core/Map/IPosition.hpp"
#include "Services/ILifecycleService.hpp"
#include "UnitId.hpp"
#include "UnitProperties.hpp"

#include <memory>

namespace sw::core
{
	struct ActionContext;
	class IMovementRuleService;
}

namespace sw::core
{
	class IMap;
	class IEventLogger;
}

namespace sw::core
{
	class Unit
	{
	protected:
		UnitId id;
		std::unique_ptr<IHealth> health;
		Movement movement;
		std::unique_ptr<IActionManager> actionManager;
		std::unique_ptr<ILifecycleService> lifecycle;
		std::unique_ptr<IActionExecutorService> actionExecutor;

	public:
		Unit(
			UnitId id,
			std::unique_ptr<IPosition> pos,
			std::unique_ptr<IHealth> health,
			std::unique_ptr<IActionManager> actionManager,
			std::unique_ptr<ILifecycleService> lifecycle,
			std::unique_ptr<IMovementRuleService> movementRule,
			std::unique_ptr<IActionExecutorService> actionExecutor,
			const UnitProperties& properties = UnitProperties{});

		virtual ~Unit() = default;

		virtual void initializeActions() = 0;

	protected:
		void addAction(std::unique_ptr<IAction> action);

	public:
		Movement& getMovement()
		{
			return movement;
		}

		const Movement& getMovement() const
		{
			return movement;
		}

		UnitId getId() const
		{
			return id;
		}

		const IPosition& getPosition() const
		{
			return movement.getPosition();
		}

		int getHp() const
		{
			return health->getHp();
		}

		const IPosition* getTargetPosition() const
		{
			return movement.getTargetPosition();
		}

		bool canMove() const
		{
			return movement.canMove();
		}

		bool hasHp() const
		{
			return health->hasHp();
		}

		bool isFlying() const
		{
			return movement.isFlying();
		}

		bool occupiesCell() const
		{
			return movement.occupiesCell();
		}

		void setPosition(std::unique_ptr<IPosition> pos)
		{
			movement.setPosition(std::move(pos));
		}

		void setTargetPosition(std::unique_ptr<IPosition> target)
		{
			movement.setTargetPosition(std::move(target));
		}

		void clearTargetPosition()
		{
			movement.clearTargetPosition();
		}

		void setHp(int hp)
		{
			health->setHp(hp);
		}

		void takeDamage(int damage);

		bool isAlive() const
		{
			return health->isAlive();
		}

		void setActionExecutor(std::unique_ptr<IActionExecutorService> executor);
		void setLifecycle(std::unique_ptr<ILifecycleService> lifecycle);

		virtual bool shouldBeRemoved() const;
		virtual bool canBeAttacked() const;
		virtual bool canAct() const;
		virtual bool isInRangedAttackRange(uint32_t distance, int minRange, int maxRange) const;

		const std::vector<std::unique_ptr<IAction>>& getActions() const
		{
			return actionManager->getActions();
		}

		bool hasActions() const
		{
			return actionManager->hasActions();
		}

		void act(ActionContext& context);
	};
}
