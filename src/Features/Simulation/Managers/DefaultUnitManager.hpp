#pragma once

#include "Core/Map/IMap.hpp"
#include "Core/Map/IPosition.hpp"
#include "Core/Simulation/Managers/IUnitManager.hpp"
#include "Core/Units/Unit.hpp"
#include "Core/Units/UnitId.hpp"

#include <functional>
#include <memory>
#include <vector>

namespace sw::features
{
	class DefaultUnitManager : public sw::core::IUnitManager
	{
	private:
		std::vector<std::unique_ptr<sw::core::Unit>> units;
		sw::core::IMap* map;

	public:
		DefaultUnitManager();

		void setMap(sw::core::IMap* map) override;
		void addUnit(std::unique_ptr<sw::core::Unit> unit) override;
		sw::core::Unit* getUnit(sw::core::UnitId id) const override;
		void removeDeadUnits() override;
		std::vector<sw::core::Unit*> getUnitsInRadius(const sw::core::IPosition& center, uint32_t radius) const override;
		std::function<sw::core::Unit*(sw::core::UnitId)> getUnitFunction() const override;
		std::function<std::vector<sw::core::Unit*>(const sw::core::IPosition&, uint32_t)> getUnitsInRadiusFunction()
			const override;
		const std::vector<std::unique_ptr<sw::core::Unit>>& getUnits() const override;
	};
}
