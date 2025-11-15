#pragma once

#include "Core/Map/IMap.hpp"
#include "Core/Map/Position.hpp"
#include "Core/Units/UnitId.hpp"

#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace sw::features
{
	class Map : public sw::core::IMap
	{
	private:
		uint32_t width;
		uint32_t height;
		std::unordered_map<sw::core::Position, std::unordered_set<sw::core::UnitId>> occupiedCells;

	public:
		Map(uint32_t width, uint32_t height);

		uint32_t getWidth() const override;
		uint32_t getHeight() const override;
		bool isValid(const sw::core::Position& pos) const override;
		bool isOccupied(const sw::core::Position& pos) const override;
		void occupy(const sw::core::Position& pos, sw::core::UnitId id) override;
		void free(const sw::core::Position& pos, sw::core::UnitId id) override;

		std::vector<sw::core::UnitId> getUnitsAt(const sw::core::Position& pos) const;
	};
}
