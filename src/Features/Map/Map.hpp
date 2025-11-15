#pragma once

#include "Core/Map/IMap.hpp"
#include "Core/Map/IPosition.hpp"
#include "Features/Map/Position2D.hpp"
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
		std::unordered_map<Position2D, std::unordered_set<sw::core::UnitId>> occupiedCells;

		Position2D toPosition2D(const sw::core::IPosition& pos) const;

	public:
		explicit Map(const std::vector<uint32_t>& dimensionSizes);

		uint32_t getDimensionSize(int index) const override;
		int getDimensionCount() const override;
		bool isValid(const sw::core::IPosition& pos) const override;
		bool isOccupied(const sw::core::IPosition& pos) const override;
		void occupy(const sw::core::IPosition& pos, sw::core::UnitId id) override;
		void free(const sw::core::IPosition& pos, sw::core::UnitId id) override;

		std::vector<sw::core::UnitId> getUnitsAt(const sw::core::IPosition& pos) const;
	};
}
