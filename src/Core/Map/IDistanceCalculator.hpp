#pragma once

#include <cstdint>

namespace sw::core
{
	class IPosition;

	class IDistanceCalculator
	{
	public:
		virtual ~IDistanceCalculator() = default;

		virtual uint32_t calculate(const IPosition& from, const IPosition& to) const = 0;
	};
}




