#pragma once

#include "Core/Map/IPosition.hpp"
#include "Core/Simulation/IEventLogger.hpp"
#include "Core/Units/UnitId.hpp"
#include "EventLog.hpp"
#include "IO/Events/MarchEnded.hpp"
#include "IO/Events/UnitAttacked.hpp"
#include "IO/Events/UnitDied.hpp"
#include "IO/Events/UnitMoved.hpp"

namespace sw::io
{
	class EventLogAdapter : public sw::core::IEventLogger
	{
	private:
		EventLog& eventLog;

	public:
		explicit EventLogAdapter(EventLog& eventLog) :
				eventLog(eventLog)
		{}

		void logUnitMoved(sw::core::UnitId unitId, const sw::core::IPosition& pos, uint64_t tick) override
		{
			eventLog.log(tick, UnitMoved{unitId, pos.getCoordinate(0), pos.getCoordinate(1)});
		}

		void logUnitAttacked(
			sw::core::UnitId attackerId,
			sw::core::UnitId targetId,
			uint32_t damage,
			uint32_t targetHp,
			uint64_t tick) override
		{
			eventLog.log(tick, UnitAttacked{attackerId, targetId, damage, targetHp});
		}

		void logUnitDied(sw::core::UnitId unitId, uint64_t tick) override
		{
			eventLog.log(tick, UnitDied{unitId});
		}

		void logMarchEnded(sw::core::UnitId unitId, const sw::core::IPosition& pos, uint64_t tick) override
		{
			eventLog.log(tick, MarchEnded{unitId, pos.getCoordinate(0), pos.getCoordinate(1)});
		}
	};
}
