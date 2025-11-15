#pragma once

#include "Core/Map/IDistanceCalculator.hpp"
#include "Core/Map/IPosition.hpp"

#include <cstdint>
#include <cstdlib>
#include <memory>
#include <optional>
#include <tuple>
#include <vector>

namespace sw::features
{
	class Position2D : public sw::core::IPosition
	{
	private:
		std::tuple<uint32_t, uint32_t> coordinates;

		std::optional<Position2D> tryCreateCellAtOffset(int32_t dx, int32_t dy, int32_t expectedDistance, const sw::core::IDistanceCalculator& calculator) const;

	public:
		Position2D() = default;

		Position2D(uint32_t x, uint32_t y) :
				coordinates(x, y)
		{}

		uint32_t getCoordinate(int index) const override
		{
			if (index == 0)
			{
				return std::get<0>(coordinates);
			}
			if (index == 1)
			{
				return std::get<1>(coordinates);
			}
			return 0;
		}

		int getDimensionCount() const override
		{
			return 2;
		}

		std::unique_ptr<sw::core::IPosition> clone() const override
		{
			return std::make_unique<Position2D>(getCoordinate(0), getCoordinate(1));
		}

		std::vector<Position2D> getCellsAtDistanceValue(int32_t distance, const sw::core::IDistanceCalculator& calculator) const;
		std::vector<std::unique_ptr<sw::core::IPosition>> getCellsAtDistance(int32_t distance, const sw::core::IDistanceCalculator& calculator) const override;
		bool isValid(const sw::core::IMap& map) const override;
		bool operator==(const sw::core::IPosition& other) const override;
		bool operator!=(const sw::core::IPosition& other) const override;

		bool operator==(const Position2D& other) const
		{
			return coordinates == other.coordinates;
		}

		bool operator!=(const Position2D& other) const
		{
			return !(*this == other);
		}
	};
}

namespace std
{
	template <>
	struct hash<sw::features::Position2D>
	{
		std::size_t operator()(const sw::features::Position2D& pos) const
		{
			return std::hash<uint32_t>()(pos.getCoordinate(0)) ^ (std::hash<uint32_t>()(pos.getCoordinate(1)) << 1);
		}
	};
}

