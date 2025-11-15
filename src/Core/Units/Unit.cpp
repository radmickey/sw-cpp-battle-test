#include "Unit.hpp"

#include "Core/Battle/Actions/ActionContext.hpp"

namespace sw::core
{
	Unit::Unit(
		UnitId id,
		std::unique_ptr<IPosition> pos,
		std::unique_ptr<IHealth> health,
		std::unique_ptr<IActionManager> actionManager,
		std::unique_ptr<ILifecycleService> lifecycle,
		std::unique_ptr<IMovementRuleService> movementRule,
		std::unique_ptr<IActionExecutorService> actionExecutor,
		const UnitProperties& properties) :
			id(id),
			health(std::move(health)),
			actionManager(std::move(actionManager)),
			movement(std::move(pos), std::move(movementRule), properties.canMove, properties.isFlying, properties.occupiesCell),
			lifecycle(std::move(lifecycle)),
			actionExecutor(std::move(actionExecutor))
	{}

	void Unit::addAction(std::unique_ptr<IAction> action)
	{
		actionManager->addAction(std::move(action));
	}

	void Unit::takeDamage(int damage)
	{
		health->takeDamage(damage);
	}

	void Unit::setActionExecutor(std::unique_ptr<IActionExecutorService> executor)
	{
		actionExecutor = std::move(executor);
	}

	void Unit::setLifecycle(std::unique_ptr<ILifecycleService> lifecycle)
	{
		this->lifecycle = std::move(lifecycle);
	}

	bool Unit::shouldBeRemoved() const
	{
		return lifecycle->shouldBeRemoved(*health);
	}

	bool Unit::canBeAttacked() const
	{
		return lifecycle->canBeAttacked(*health);
	}

	bool Unit::canAct() const
	{
		return isAlive() && hasActions();
	}

	bool Unit::isInRangedAttackRange(uint32_t distance, int minRange, int maxRange) const
	{
		return distance >= static_cast<uint32_t>(minRange) && distance <= static_cast<uint32_t>(maxRange);
	}

	void Unit::act(ActionContext& context)
	{
		if (actionExecutor)
		{
			actionExecutor->execute(*this, context);
		}
	}
}
