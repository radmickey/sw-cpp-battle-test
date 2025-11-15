#include "ActionExecutorService.hpp"

#include "Core/Battle/Actions/ActionContext.hpp"
#include "Core/Units/Unit.hpp"

namespace sw::features
{
	bool ActionExecutorService::execute(sw::core::Unit& unit, sw::core::ActionContext& context)
	{
		for (auto& action : unit.getActions())
		{
			if (action->canExecute(unit, context))
			{
				action->execute(unit, context);
				return true;
			}
		}
		return false;
	}
}
