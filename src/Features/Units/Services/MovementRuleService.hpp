#pragma once

#include "Core/Map/IPosition.hpp"
#include "Core/Units/Components/Movement/IMovementRuleService.hpp"

#include <memory>
#include <optional>
#include <vector>

namespace sw::core
{
	class IMap;
}

namespace sw::features
{
	class MovementRuleService : public sw::core::IMovementRuleService
	{
	public:
		std::vector<std::unique_ptr<sw::core::IPosition>> collectReachablePositions(
			const sw::core::IPosition& currentPos,
			const sw::core::IMap& map,
			uint32_t moveDistance,
			bool needsFreeCell) const override;
		std::unique_ptr<sw::core::IPosition> findBestPosition(
			const std::vector<std::unique_ptr<sw::core::IPosition>>& reachablePositions,
			const sw::core::IPosition& currentPos,
			const sw::core::IPosition* targetPos) const override;
	};
}
