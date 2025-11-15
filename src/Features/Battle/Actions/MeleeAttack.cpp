#include "MeleeAttack.hpp"

#include "Core/Battle/Actions/ActionContext.hpp"
#include "Core/Simulation/IEventLogger.hpp"
#include "Core/Units/Unit.hpp"

#include <algorithm>
#include <iterator>
#include <random>

namespace sw::features
{
	using sw::core::ActionCheckContext;
	using sw::core::ActionContext;
	using sw::core::Position;
	using sw::core::Unit;

	MeleeAttack::MeleeAttack(int damage) :
			damage(damage)
	{}

	std::vector<Unit*> MeleeAttack::findValidTargets(const Unit& actor, const ActionCheckContext& context) const
	{
		Position actorPos = actor.getPosition();
		auto adjacentCells = actorPos.getCellsAtDistance(1);

		std::vector<Unit*> validTargets;

		for (const auto& cell : adjacentCells)
		{
			auto unitsAtCell = context.getUnitsInRadius(cell, 0);

			for (Unit* target : unitsAtCell)
			{
				if (target && target->getId() != actor.getId() && target->canBeAttacked())
				{
					validTargets.push_back(target);
				}
			}
		}

		return validTargets;
	}

	bool MeleeAttack::canExecute(const Unit& actor, const ActionCheckContext& context)
	{
		return !findValidTargets(actor, context).empty();
	}

	void MeleeAttack::execute(Unit& actor, ActionContext& context)
	{
		auto validTargets = findValidTargets(actor, context);
		if (validTargets.empty())
		{
			return;
		}

		std::uniform_int_distribution<size_t> dist(0, validTargets.size() - 1);
		Unit* target = validTargets[dist(context.rng)];

		performAttack(actor, target, damage, context.logger, context.currentTick);
	}
}
