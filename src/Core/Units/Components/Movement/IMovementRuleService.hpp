#pragma once

#include "Core/Map/IPosition.hpp"

#include <memory>
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
		virtual std::vector<std::unique_ptr<IPosition>> collectReachablePositions(
			const IPosition& currentPos, const IMap& map, uint32_t moveDistance, bool needsFreeCell) const
			= 0;
		virtual std::unique_ptr<IPosition> findBestPosition(
			const std::vector<std::unique_ptr<IPosition>>& reachablePositions,
			const IPosition& currentPos,
			const IPosition* targetPos) const
			= 0;
	};
}
