#pragma once

namespace sw::core
{
	class Health;

	class ILifecycleService
	{
	public:
		virtual ~ILifecycleService() = default;
		virtual bool shouldBeRemoved(const Health& health) const = 0;
		virtual bool canBeAttacked(const Health& health) const = 0;
	};
}
