#include "MovementRuleService.hpp"

#include "Core/Map/IMap.hpp"
#include "Features/Map/Map.hpp"

namespace sw::features
{
	std::vector<sw::core::Position> MovementRuleService::collectReachablePositions(
		const sw::core::Position& currentPos,
		const sw::core::IMap& map,
		uint32_t moveDistance,
		bool needsFreeCell) const
	{
		std::vector<sw::core::Position> reachablePositions;

		for (uint32_t d = 1; d <= moveDistance; ++d)
		{
			auto cellsAtDistance = currentPos.getCellsAtDistance(static_cast<int32_t>(d));
			for (const auto& pos : cellsAtDistance)
			{
				if (!map.isValid(pos))
				{
					continue;
				}

				if (needsFreeCell && map.isOccupied(pos))
				{
					continue;
				}

				reachablePositions.push_back(pos);
			}
		}

		return reachablePositions;
	}

	sw::core::Position MovementRuleService::findBestPosition(
		const std::vector<sw::core::Position>& reachablePositions,
		const sw::core::Position& currentPos,
		const std::optional<sw::core::Position>& targetPos) const
	{
		if (!targetPos.has_value())
		{
			return currentPos;
		}

		sw::core::Position bestPos = currentPos;
		uint32_t minDistance = currentPos.chebyshevDistance(*targetPos);

		for (const auto& pos : reachablePositions)
		{
			uint32_t dist = pos.chebyshevDistance(*targetPos);
			if (dist < minDistance)
			{
				minDistance = dist;
				bestPos = pos;
			}
		}

		return bestPos;
	}
}
