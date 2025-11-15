#include "MapManager.hpp"

#include "Core/Map/IMap.hpp"
#include "Features/Map/Map.hpp"

namespace sw::features
{
	void MapManager::createMap(const std::vector<uint32_t>& dimensionSizes)
	{
		map = std::make_unique<Map>(dimensionSizes);
	}

	sw::core::IMap* MapManager::getMap() const
	{
		return map.get();
	}

	bool MapManager::hasMap() const
	{
		return map != nullptr;
	}
}
