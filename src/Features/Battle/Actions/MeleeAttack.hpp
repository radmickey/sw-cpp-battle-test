#pragma once

#include "Features/Battle/Actions/AttackAction.hpp"

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
	using sw::core::Unit;

	class MeleeAttack : public AttackAction
	{
	private:
		int damage;

		std::vector<Unit*> findValidTargets(const Unit& actor, const ActionCheckContext& context) const;

	public:
		explicit MeleeAttack(int damage);

		bool canExecute(const Unit& actor, const ActionCheckContext& context) override;
		void execute(Unit& actor, ActionContext& context) override;
	};
}
