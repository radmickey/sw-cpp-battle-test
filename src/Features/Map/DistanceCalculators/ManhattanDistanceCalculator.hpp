#pragma once

#include "Core/Map/IDistanceCalculator.hpp"

namespace sw::features
{
	class ManhattanDistanceCalculator : public sw::core::IDistanceCalculator
	{
	public:
		uint32_t calculate(const sw::core::IPosition& from, const sw::core::IPosition& to) const override;
	};
}




