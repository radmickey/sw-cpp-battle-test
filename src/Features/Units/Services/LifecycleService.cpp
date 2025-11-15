#include "LifecycleService.hpp"

#include "Core/Units/Components/Health/IHealth.hpp"

namespace sw::features
{
	bool LifecycleService::shouldBeRemoved(const sw::core::IHealth& health) const
	{
		return !health.isAlive();
	}

	bool LifecycleService::canBeAttacked(const sw::core::IHealth& health) const
	{
		return health.isAlive();
	}
}
