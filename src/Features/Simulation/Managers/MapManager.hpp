#pragma once

#include "Core/Simulation/Managers/IMapManager.hpp"

#include <memory>

namespace sw::features
{
	class MapManager : public sw::core::IMapManager
	{
	private:
		std::unique_ptr<sw::core::IMap> map;

	public:
		void createMap(const std::vector<uint32_t>& dimensionSizes) override;
		sw::core::IMap* getMap() const override;
		bool hasMap() const override;
	};
}
