#include "LifecycleService.hpp"

#include "Core/Units/Components/Health/Health.hpp"

namespace sw::features
{
	bool LifecycleService::shouldBeRemoved(const sw::core::Health& health) const
	{
		return !health.isAlive();
	}

	bool LifecycleService::canBeAttacked(const sw::core::Health& health) const
	{
		return health.isAlive();
	}
}
