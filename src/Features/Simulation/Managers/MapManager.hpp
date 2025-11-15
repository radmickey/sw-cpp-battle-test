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
		void createMap(uint32_t width, uint32_t height) override;
		sw::core::IMap* getMap() const override;
		bool hasMap() const override;
	};
}
