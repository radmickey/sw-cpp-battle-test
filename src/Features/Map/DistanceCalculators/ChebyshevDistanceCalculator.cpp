#include "ChebyshevDistanceCalculator.hpp"

#include "Core/Map/IPosition.hpp"

#include <algorithm>

namespace sw::features
{
	uint32_t ChebyshevDistanceCalculator::calculate(const sw::core::IPosition& from, const sw::core::IPosition& to) const
	{
		if (from.getDimensionCount() != to.getDimensionCount())
		{
			return 0;
		}

		uint32_t maxDiff = 0;
		for (int i = 0; i < from.getDimensionCount(); ++i)
		{
			uint32_t diff = (from.getCoordinate(i) > to.getCoordinate(i))
				? (from.getCoordinate(i) - to.getCoordinate(i))
				: (to.getCoordinate(i) - from.getCoordinate(i));
			maxDiff = std::max(maxDiff, diff);
		}
		return maxDiff;
	}
}




