#pragma once

#include "Unit.hpp"

#include <memory>

namespace sw::core
{
	class UnitFactory
	{
	public:
		template <typename TUnit, typename... Args>
		std::unique_ptr<Unit> create(Args&&... args)
		{
			auto unit = std::make_unique<TUnit>(std::forward<Args>(args)...);
			unit->initializeActions();
			return unit;
		}
	};
}
