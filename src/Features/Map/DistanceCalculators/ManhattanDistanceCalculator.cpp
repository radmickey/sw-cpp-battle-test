#include "ManhattanDistanceCalculator.hpp"

#include "Core/Map/IPosition.hpp"

namespace sw::features
{
	uint32_t ManhattanDistanceCalculator::calculate(const sw::core::IPosition& from, const sw::core::IPosition& to) const
	{
		if (from.getDimensionCount() != to.getDimensionCount())
		{
			return 0;
		}

		uint32_t sum = 0;
		for (int i = 0; i < from.getDimensionCount(); ++i)
		{
			uint32_t diff = (from.getCoordinate(i) > to.getCoordinate(i))
				? (from.getCoordinate(i) - to.getCoordinate(i))
				: (to.getCoordinate(i) - from.getCoordinate(i));
			sum += diff;
		}
		return sum;
	}
}




