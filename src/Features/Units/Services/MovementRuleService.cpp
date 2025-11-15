#include "MovementRuleService.hpp"

#include "Core/Map/IMap.hpp"
#include "Features/Map/Map.hpp"
#include "Features/Map/Position2D.hpp"
#include "Features/Map/DistanceCalculators/ChebyshevDistanceCalculator.hpp"

namespace sw::features
{
	std::vector<std::unique_ptr<sw::core::IPosition>> MovementRuleService::collectReachablePositions(
		const sw::core::IPosition& currentPos,
		const sw::core::IMap& map,
		uint32_t moveDistance,
		bool needsFreeCell) const
	{
		std::vector<std::unique_ptr<sw::core::IPosition>> reachablePositions;
		ChebyshevDistanceCalculator calculator;

		const Position2D* pos2d = dynamic_cast<const Position2D*>(&currentPos);
		if (!pos2d)
		{
			return reachablePositions;
		}

		for (uint32_t d = 1; d <= moveDistance; ++d)
		{
			auto cellsAtDistance = pos2d->getCellsAtDistanceValue(static_cast<int32_t>(d), calculator);
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

				reachablePositions.push_back(std::make_unique<Position2D>(pos));
			}
		}

		return reachablePositions;
	}

	std::unique_ptr<sw::core::IPosition> MovementRuleService::findBestPosition(
		const std::vector<std::unique_ptr<sw::core::IPosition>>& reachablePositions,
		const sw::core::IPosition& currentPos,
		const sw::core::IPosition* targetPos) const
	{
		if (!targetPos)
		{
			return currentPos.clone();
		}

		ChebyshevDistanceCalculator calculator;
		std::unique_ptr<sw::core::IPosition> bestPos = currentPos.clone();
		uint32_t minDistance = calculator.calculate(currentPos, *targetPos);

		for (const auto& pos : reachablePositions)
		{
			if (!pos)
			{
				continue;
			}
			uint32_t dist = calculator.calculate(*pos, *targetPos);
			if (dist < minDistance)
			{
				minDistance = dist;
				bestPos = pos->clone();
			}
		}

		return bestPos;
	}
}
