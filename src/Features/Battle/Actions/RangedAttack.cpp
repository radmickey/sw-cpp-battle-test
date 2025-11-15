#include "RangedAttack.hpp"

#include "Core/Battle/Actions/ActionContext.hpp"
#include "Core/Simulation/IEventLogger.hpp"
#include "Core/Units/Unit.hpp"

#include <algorithm>
#include <random>
#include <vector>

namespace sw::features
{
	using sw::core::ActionCheckContext;
	using sw::core::ActionContext;
	using sw::core::Position;
	using sw::core::Unit;

	RangedAttack::RangedAttack(int minRange, int maxRange, int damage, bool requiresNoAdjacentUnits) :
			minRange(minRange),
			maxRange(maxRange),
			damage(damage),
			requiresNoAdjacentUnits(requiresNoAdjacentUnits)
	{}

	bool RangedAttack::hasNoAdjacentUnits(const Unit& actor, const ActionCheckContext& context) const
	{
		Position actorPos = actor.getPosition();
		auto adjacentCells = actorPos.getCellsAtDistance(1);

		for (const auto& cell : adjacentCells)
		{
			auto unitsAtCell = context.getUnitsInRadius(cell, 0);

			for (Unit* unit : unitsAtCell)
			{
				if (unit && unit->getId() != actor.getId() && unit->canBeAttacked())
				{
					return false;
				}
			}
		}

		return true;
	}

	bool RangedAttack::isValidTarget(
		Unit* target, const Unit& actor, const Position& pos, const Position& actorPos) const
	{
		if (!target || !target->canBeAttacked())
		{
			return false;
		}

		uint32_t dist = actorPos.distance(pos);
		return target->isInRangedAttackRange(dist, minRange, maxRange);
	}

	std::vector<Unit*> RangedAttack::findTargets(const Unit& actor, const ActionCheckContext& context) const
	{
		std::vector<Unit*> targets;
		Position actorPos = actor.getPosition();

		auto candidates = context.getUnitsInRadius(actorPos, static_cast<uint32_t>(maxRange));

		for (Unit* target : candidates)
		{
			if (!target || target->getId() == actor.getId())
			{
				continue;
			}

			Position targetPos = target->getPosition();
			if (isValidTarget(target, actor, targetPos, actorPos))
			{
				targets.push_back(target);
			}
		}

		return targets;
	}

	bool RangedAttack::canPerformRangedAttack(const Unit& actor, const ActionCheckContext& context) const
	{
		if (requiresNoAdjacentUnits && !hasNoAdjacentUnits(actor, context))
		{
			return false;
		}

		auto targets = findTargets(actor, context);
		return !targets.empty();
	}

	bool RangedAttack::canExecute(const Unit& actor, const ActionCheckContext& context)
	{
		return canPerformRangedAttack(actor, context);
	}

	void RangedAttack::execute(Unit& actor, ActionContext& context)
	{
		if (!canPerformRangedAttack(actor, context))
		{
			return;
		}

		auto targets = findTargets(actor, context);
		if (targets.empty())
		{
			return;
		}

		std::uniform_int_distribution<size_t> dist(0, targets.size() - 1);
		Unit* target = targets[dist(context.rng)];

		performAttack(actor, target, damage, context.logger, context.currentTick);
	}
}
