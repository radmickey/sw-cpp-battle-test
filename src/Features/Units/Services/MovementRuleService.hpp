#pragma once

#include "Core/Map/Position.hpp"
#include "Core/Units/Components/Movement/IMovementRuleService.hpp"

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
		std::vector<sw::core::Position> collectReachablePositions(
			const sw::core::Position& currentPos,
			const sw::core::IMap& map,
			uint32_t moveDistance,
			bool needsFreeCell) const override;
		sw::core::Position findBestPosition(
			const std::vector<sw::core::Position>& reachablePositions,
			const sw::core::Position& currentPos,
			const std::optional<sw::core::Position>& targetPos) const override;
	};
}
