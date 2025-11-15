#pragma once

#include <cstdint>
#include <cstdlib>
#include <optional>
#include <vector>

namespace sw::core
{
	struct Position
	{
		uint32_t x;
		uint32_t y;

		Position() = default;

		Position(uint32_t x, uint32_t y) :
				x(x),
				y(y)
		{}

		std::pair<uint32_t, uint32_t> getDifferences(const Position& other) const
		{
			uint32_t dx = (x > other.x) ? (x - other.x) : (other.x - x);
			uint32_t dy = (y > other.y) ? (y - other.y) : (other.y - y);
			return {dx, dy};
		}

		uint32_t manhattanDistance(const Position& other) const
		{
			auto [dx, dy] = getDifferences(other);
			return dx + dy;
		}

		uint32_t chebyshevDistance(const Position& other) const
		{
			auto [dx, dy] = getDifferences(other);
			return (dx > dy) ? dx : dy;
		}

		uint32_t distance(const Position& other) const
		{
			return manhattanDistance(other);
		}

		std::vector<Position> getCellsAtDistance(int32_t distance) const
		{
			std::vector<Position> result;
			if (distance <= 0)
			{
				return result;
			}

			for (int32_t dx = -distance; dx <= distance; ++dx)
			{
				for (int32_t dy = -distance; dy <= distance; ++dy)
				{
					if (auto pos = tryCreateCellAtOffset(dx, dy, distance))
					{
						result.push_back(*pos);
					}
				}
			}
			return result;
		}

	private:
		std::optional<Position> tryCreateCellAtOffset(int32_t dx, int32_t dy, int32_t expectedDistance) const
		{
			if (dx == 0 && dy == 0)
			{
				return std::nullopt;
			}

			int64_t newX = static_cast<int64_t>(x) + dx;
			int64_t newY = static_cast<int64_t>(y) + dy;
			if (newX < 0 || newY < 0)
			{
				return std::nullopt;
			}

			Position candidatePos(static_cast<uint32_t>(newX), static_cast<uint32_t>(newY));
			if (static_cast<int32_t>(chebyshevDistance(candidatePos)) != expectedDistance)
			{
				return std::nullopt;
			}

			return candidatePos;
		}

	public:
		bool isValid(uint32_t width, uint32_t height) const
		{
			return x < width && y < height;
		}

		bool operator==(const Position& other) const
		{
			return x == other.x && y == other.y;
		}

		bool operator!=(const Position& other) const
		{
			return !(*this == other);
		}
	};
}

namespace std
{
	template <>
	struct hash<sw::core::Position>
	{
		std::size_t operator()(const sw::core::Position& pos) const
		{
			return std::hash<uint32_t>()(pos.x) ^ (std::hash<uint32_t>()(pos.y) << 1);
		}
	};
}
