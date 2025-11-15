#pragma once

namespace sw::core
{
	class IHealth;

	class ILifecycleService
	{
	public:
		virtual ~ILifecycleService() = default;
		virtual bool shouldBeRemoved(const IHealth& health) const = 0;
		virtual bool canBeAttacked(const IHealth& health) const = 0;
	};
}
