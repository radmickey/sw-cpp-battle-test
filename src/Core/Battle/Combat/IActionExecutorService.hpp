#pragma once

namespace sw::core
{
	class Unit;
	struct ActionContext;
}

namespace sw::core
{
	class IActionExecutorService
	{
	public:
		virtual ~IActionExecutorService() = default;
		virtual bool execute(Unit& unit, ActionContext& context) = 0;
	};
}
