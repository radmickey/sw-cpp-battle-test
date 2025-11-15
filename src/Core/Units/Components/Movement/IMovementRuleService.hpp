#pragma once

#include "Core/Map/Position.hpp"

#include <optional>
#include <vector>

namespace sw::core
{
	class IMap;
}

namespace sw::core
{
	class IMovementRuleService
	{
	public:
		virtual ~IMovementRuleService() = default;
		virtual std::vector<Position> collectReachablePositions(
			const Position& currentPos, const IMap& map, uint32_t moveDistance, bool needsFreeCell) const
			= 0;
		virtual Position findBestPosition(
			const std::vector<Position>& reachablePositions,
			const Position& currentPos,
			const std::optional<Position>& targetPos) const
			= 0;
	};
}
