#pragma once

namespace sw::core
{
	class Unit;
}

namespace sw::core
{
	class IActionAvailabilityChecker
	{
	public:
		virtual ~IActionAvailabilityChecker() = default;
		virtual bool hasAvailableAction(const Unit& unit) const = 0;
	};
}
