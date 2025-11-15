#pragma once

#include "Features/Battle/Actions/AttackAction.hpp"
#include "Core/Map/IPosition.hpp"

#include <vector>

namespace sw::core
{
	class Unit;
	struct ActionCheckContext;
	struct ActionContext;
}

namespace sw::features
{
	using sw::core::ActionCheckContext;
	using sw::core::ActionContext;
	using sw::core::IPosition;
	using sw::core::Unit;

	class RangedAttack : public AttackAction
	{
	private:
		int minRange;
		int maxRange;
		int damage;
		bool requiresNoAdjacentUnits;

		bool hasNoAdjacentUnits(const Unit& actor, const ActionCheckContext& context) const;
		bool isValidTarget(Unit* target, const Unit& actor, const IPosition& pos, const IPosition& actorPos) const;
		std::vector<Unit*> findTargets(const Unit& actor, const ActionCheckContext& context) const;
		bool canPerformRangedAttack(const Unit& actor, const ActionCheckContext& context) const;

	public:
		RangedAttack(int minRange, int maxRange, int damage, bool requiresNoAdjacentUnits = false);

		bool canExecute(const Unit& actor, const ActionCheckContext& context) override;
		void execute(Unit& actor, ActionContext& context) override;
	};
}
