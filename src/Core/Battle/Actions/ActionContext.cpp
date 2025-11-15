#include "ActionContext.hpp"

#include "Core/Map/IMap.hpp"

namespace sw::core
{
	ActionCheckContext::ActionCheckContext(
		IMap& map,
		std::function<Unit*(UnitId)> getUnit,
		std::function<std::vector<Unit*>(const IPosition&, uint32_t)> getUnitsInRadius) :
			map(map),
			getUnit(std::move(getUnit)),
			getUnitsInRadius(std::move(getUnitsInRadius))
	{}

	ActionContext::ActionContext(
		IMap& map,
		IEventLogger& logger,
		std::mt19937& rng,
		uint64_t currentTick,
		std::function<Unit*(UnitId)> getUnit,
		std::function<std::vector<Unit*>(const IPosition&, uint32_t)> getUnitsInRadius) :
			ActionCheckContext(map, getUnit, getUnitsInRadius),
			logger(logger),
			rng(rng),
			currentTick(currentTick)
	{}
}
