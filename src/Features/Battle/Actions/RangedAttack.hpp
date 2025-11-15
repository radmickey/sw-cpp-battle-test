#pragma once

#include "Core/Battle/Actions/Action.hpp"
#include "Core/Map/Position.hpp"

#include <vector>

namespace sw::core
{
	class Unit;
	struct ActionCheckContext;
	struct ActionContext;
}

namespace sw::features
{
	using sw::core::Action;
	using sw::core::ActionCheckContext;
	using sw::core::ActionContext;
	using sw::core::Position;
	using sw::core::Unit;

	class RangedAttack : public Action
	{
	private:
		int minRange;
		int maxRange;
		int damage;
		bool requiresNoAdjacentUnits;

		bool hasNoAdjacentUnits(const Unit& actor, const ActionCheckContext& context) const;
		bool isValidTarget(Unit* target, const Unit& actor, const Position& pos, const Position& actorPos) const;
		std::vector<Unit*> findTargets(const Unit& actor, const ActionCheckContext& context) const;
		bool canPerformRangedAttack(const Unit& actor, const ActionCheckContext& context) const;

	public:
		RangedAttack(int minRange, int maxRange, int damage, bool requiresNoAdjacentUnits = false);

		bool canExecute(const Unit& actor, const ActionCheckContext& context) override;
		void execute(Unit& actor, ActionContext& context) override;
	};
}
