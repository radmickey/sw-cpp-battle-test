#pragma once

#include <cstdint>
#include <vector>

namespace sw::core
{
	class IDistanceCalculator;
	class IMap;

	class IPosition
	{
	public:
		virtual ~IPosition() = default;

		virtual uint32_t getCoordinate(int index) const = 0;
		virtual int getDimensionCount() const = 0;
		virtual std::vector<std::unique_ptr<IPosition>> getCellsAtDistance(int32_t distance, const IDistanceCalculator& calculator) const = 0;
		virtual bool isValid(const IMap& map) const = 0;
		virtual bool operator==(const IPosition& other) const = 0;
		virtual bool operator!=(const IPosition& other) const = 0;

		virtual std::unique_ptr<IPosition> clone() const = 0;
	};
}

