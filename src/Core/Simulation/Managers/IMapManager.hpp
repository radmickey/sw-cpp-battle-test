#pragma once

#include <cstdint>
#include <vector>

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

		virtual void createMap(const std::vector<uint32_t>& dimensionSizes) = 0;
		virtual IMap* getMap() const = 0;
		virtual bool hasMap() const = 0;
	};
}
