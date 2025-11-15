#pragma once

#include "Core/Units/Services/ILifecycleService.hpp"

namespace sw::core
{
	class Health;
}

namespace sw::features
{
	class LifecycleService : public sw::core::ILifecycleService
	{
	public:
		bool shouldBeRemoved(const sw::core::Health& health) const override;
		bool canBeAttacked(const sw::core::Health& health) const override;
	};
}
