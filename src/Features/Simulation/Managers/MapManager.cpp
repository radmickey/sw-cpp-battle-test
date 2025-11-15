#include "MapManager.hpp"

#include "Core/Map/IMap.hpp"
#include "Features/Map/Map.hpp"

namespace sw::features
{
	void MapManager::createMap(uint32_t width, uint32_t height)
	{
		map = std::make_unique<Map>(width, height);
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
