#pragma once

namespace sw::core
{
	class Unit;
	struct ActionContext;
	struct ActionCheckContext;
}

namespace sw::core
{
	class IAction
	{
	public:
		virtual ~IAction() = default;

		virtual bool canExecute(const Unit& actor, const ActionCheckContext& context) = 0;
		virtual void execute(Unit& actor, ActionContext& context) = 0;
	};
}
