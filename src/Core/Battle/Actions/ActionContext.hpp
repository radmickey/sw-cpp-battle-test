#pragma once

#include "Core/Map/IPosition.hpp"
#include "Core/Units/UnitId.hpp"

#include <cstdint>
#include <functional>
#include <random>
#include <vector>

namespace sw::core
{
	class Unit;
	class IMap;
	class IEventLogger;
}

namespace sw::core
{
	struct ActionCheckContext
	{
		IMap& map;
		std::function<Unit*(UnitId)> getUnit;
		std::function<std::vector<Unit*>(const IPosition&, uint32_t)> getUnitsInRadius;

		ActionCheckContext(
			IMap& map,
			std::function<Unit*(UnitId)> getUnit,
			std::function<std::vector<Unit*>(const IPosition&, uint32_t)> getUnitsInRadius);
	};

	struct ActionContext : public ActionCheckContext
	{
		IEventLogger& logger;
		std::mt19937& rng;
		uint64_t currentTick;

		ActionContext(
			IMap& map,
			IEventLogger& logger,
			std::mt19937& rng,
			uint64_t currentTick,
			std::function<Unit*(UnitId)> getUnit,
			std::function<std::vector<Unit*>(const IPosition&, uint32_t)> getUnitsInRadius);
	};
}
