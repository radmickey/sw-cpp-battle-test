#include "MeleeAttack.hpp"

#include "AttackAction.hpp"
#include "Core/Battle/Actions/ActionContext.hpp"
#include "Core/Units/Unit.hpp"
#include "Features/Map/Position2D.hpp"
#include "Features/Map/DistanceCalculators/ChebyshevDistanceCalculator.hpp"

#include <algorithm>
#include <iterator>
#include <random>

namespace sw::features
{
	using sw::core::ActionCheckContext;
	using sw::core::ActionContext;
	using sw::core::Unit;

	MeleeAttack::MeleeAttack(int damage) :
			damage(damage)
	{}

	std::vector<Unit*> MeleeAttack::findValidTargets(const Unit& actor, const ActionCheckContext& context) const
	{
		const sw::core::IPosition& actorPosRef = actor.getPosition();
		const Position2D* actorPos = dynamic_cast<const Position2D*>(&actorPosRef);
		if (!actorPos)
		{
			return {};
		}
		ChebyshevDistanceCalculator calculator;
		auto adjacentCells = actorPos->getCellsAtDistanceValue(1, calculator);

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
