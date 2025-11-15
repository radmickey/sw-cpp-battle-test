#pragma once

#include "Core/Map/IPosition.hpp"
#include "Core/Units/UnitId.hpp"

#include <cstdint>
#include <functional>

namespace sw::core
{
	class IEventLogger
	{
	public:
		virtual ~IEventLogger() = default;

		virtual void logUnitMoved(UnitId unitId, const IPosition& pos, uint64_t tick) = 0;
		virtual void logUnitAttacked(
			UnitId attackerId, UnitId targetId, uint32_t damage, uint32_t targetHp, uint64_t tick)
			= 0;
		virtual void logUnitDied(UnitId unitId, uint64_t tick) = 0;
		virtual void logMarchEnded(UnitId unitId, const IPosition& pos, uint64_t tick) = 0;
	};
}
