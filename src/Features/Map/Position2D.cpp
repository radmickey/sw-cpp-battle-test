#include "Position2D.hpp"

#include "Core/Map/IDistanceCalculator.hpp"
#include "Core/Map/IMap.hpp"

#include <algorithm>
#include <memory>

namespace sw::features
{
	std::optional<Position2D> Position2D::tryCreateCellAtOffset(int32_t dx, int32_t dy, int32_t expectedDistance, const sw::core::IDistanceCalculator& calculator) const
	{
		if (dx == 0 && dy == 0)
		{
			return std::nullopt;
		}

		uint32_t x = getCoordinate(0);
		uint32_t y = getCoordinate(1);
		int64_t newX = static_cast<int64_t>(x) + dx;
		int64_t newY = static_cast<int64_t>(y) + dy;
		if (newX < 0 || newY < 0)
		{
			return std::nullopt;
		}

		Position2D candidatePos(static_cast<uint32_t>(newX), static_cast<uint32_t>(newY));
		if (static_cast<int32_t>(calculator.calculate(*this, candidatePos)) != expectedDistance)
		{
			return std::nullopt;
		}

		return candidatePos;
	}

	std::vector<Position2D> Position2D::getCellsAtDistanceValue(int32_t distance, const sw::core::IDistanceCalculator& calculator) const
	{
		std::vector<Position2D> result;
		if (distance <= 0)
		{
			return result;
		}

		for (int32_t dx = -distance; dx <= distance; ++dx)
		{
			for (int32_t dy = -distance; dy <= distance; ++dy)
			{
				if (auto pos = tryCreateCellAtOffset(dx, dy, distance, calculator))
				{
					result.push_back(*pos);
				}
			}
		}
		return result;
	}

	std::vector<std::unique_ptr<sw::core::IPosition>> Position2D::getCellsAtDistance(int32_t distance, const sw::core::IDistanceCalculator& calculator) const
	{
		std::vector<std::unique_ptr<sw::core::IPosition>> result;
		auto positions = getCellsAtDistanceValue(distance, calculator);
		for (const auto& pos : positions)
		{
			result.push_back(std::make_unique<Position2D>(pos));
		}
		return result;
	}

	bool Position2D::isValid(const sw::core::IMap& map) const
	{
		if (getDimensionCount() != map.getDimensionCount())
		{
			return false;
		}
		for (int i = 0; i < getDimensionCount(); ++i)
		{
			uint32_t coord = getCoordinate(i);
			if (coord >= map.getDimensionSize(i))
			{
				return false;
			}
		}
		return true;
	}

	bool Position2D::operator==(const sw::core::IPosition& other) const
	{
		if (getDimensionCount() != other.getDimensionCount())
		{
			return false;
		}
		for (int i = 0; i < getDimensionCount(); ++i)
		{
			if (getCoordinate(i) != other.getCoordinate(i))
			{
				return false;
			}
		}
		return true;
	}

	bool Position2D::operator!=(const sw::core::IPosition& other) const
	{
		return !(*this == other);
	}
}

