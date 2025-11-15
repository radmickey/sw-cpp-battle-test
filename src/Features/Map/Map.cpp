#include "Map.hpp"

namespace sw::features
{
	Map::Map(uint32_t width, uint32_t height) :
			width(width),
			height(height)
	{}

	uint32_t Map::getWidth() const
	{
		return width;
	}

	uint32_t Map::getHeight() const
	{
		return height;
	}

	bool Map::isValid(const sw::core::Position& pos) const
	{
		return pos.isValid(width, height);
	}

	bool Map::isOccupied(const sw::core::Position& pos) const
	{
		auto it = occupiedCells.find(pos);
		return it != occupiedCells.end() && !it->second.empty();
	}

	void Map::occupy(const sw::core::Position& pos, sw::core::UnitId id)
	{
		if (!isValid(pos))
		{
			throw std::runtime_error("Position out of bounds");
		}
		auto& unitsAtPos = occupiedCells[pos];
		if (!unitsAtPos.empty() && unitsAtPos.find(id) == unitsAtPos.end())
		{
			throw std::runtime_error("Cell already occupied");
		}
		unitsAtPos.insert(id);
	}

	void Map::free(const sw::core::Position& pos, sw::core::UnitId id)
	{
		auto it = occupiedCells.find(pos);
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

	std::vector<sw::core::UnitId> Map::getUnitsAt(const sw::core::Position& pos) const
	{
		auto it = occupiedCells.find(pos);
		if (it != occupiedCells.end())
		{
			return std::vector<sw::core::UnitId>(it->second.begin(), it->second.end());
		}
		return {};
	}
}
