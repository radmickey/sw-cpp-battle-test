#pragma once

#include "Core/Battle/Combat/IActionExecutorService.hpp"

namespace sw::core
{
	class Unit;
	struct ActionContext;
}

namespace sw::features
{
	class ActionExecutorService : public sw::core::IActionExecutorService
	{
	public:
		bool execute(sw::core::Unit& unit, sw::core::ActionContext& context) override;
	};
}
