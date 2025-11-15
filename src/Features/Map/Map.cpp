#include "Map.hpp"

namespace sw::features
{
	Position2D Map::toPosition2D(const sw::core::IPosition& pos) const
	{
		return Position2D(pos.getCoordinate(0), pos.getCoordinate(1));
	}

	Map::Map(const std::vector<uint32_t>& dimensionSizes) :
			width(dimensionSizes.size() > 0 ? dimensionSizes[0] : 0),
			height(dimensionSizes.size() > 1 ? dimensionSizes[1] : 0)
	{}

	uint32_t Map::getDimensionSize(int index) const
	{
		if (index == 0)
		{
			return width;
		}
		if (index == 1)
		{
			return height;
		}
		return 0;
	}

	int Map::getDimensionCount() const
	{
		return 2;
	}

	bool Map::isValid(const sw::core::IPosition& pos) const
	{
		return pos.isValid(*this);
	}

	bool Map::isOccupied(const sw::core::IPosition& pos) const
	{
		Position2D pos2d = toPosition2D(pos);
		auto it = occupiedCells.find(pos2d);
		return it != occupiedCells.end() && !it->second.empty();
	}

	void Map::occupy(const sw::core::IPosition& pos, sw::core::UnitId id)
	{
		if (!isValid(pos))
		{
			throw std::runtime_error("Position out of bounds");
		}
		Position2D pos2d = toPosition2D(pos);
		auto& unitsAtPos = occupiedCells[pos2d];
		if (!unitsAtPos.empty() && unitsAtPos.find(id) == unitsAtPos.end())
		{
			throw std::runtime_error("Cell already occupied");
		}
		unitsAtPos.insert(id);
	}

	void Map::free(const sw::core::IPosition& pos, sw::core::UnitId id)
	{
		Position2D pos2d = toPosition2D(pos);
		auto it = occupiedCells.find(pos2d);
		if (it != occupiedCells.end())
		{
			auto& unitsAtPos = it->second;
			unitsAtPos.erase(id);
			if (unitsAtPos.empty())
			{
				occupiedCells.erase(it);
			}
		}
	}

	std::vector<sw::core::UnitId> Map::getUnitsAt(const sw::core::IPosition& pos) const
	{
		Position2D pos2d = toPosition2D(pos);
		auto it = occupiedCells.find(pos2d);
		if (it != occupiedCells.end())
		{
			return std::vector<sw::core::UnitId>(it->second.begin(), it->second.end());
		}
		return {};
	}
}
