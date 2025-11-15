#pragma once

#include <cstdint>

namespace sw::core
{
	class IMap;
}

namespace sw::core
{
	class IMapManager
	{
	public:
		virtual ~IMapManager() = default;

		virtual void createMap(uint32_t width, uint32_t height) = 0;
		virtual IMap* getMap() const = 0;
		virtual bool hasMap() const = 0;
	};
}
