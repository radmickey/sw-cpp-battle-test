#pragma once

#include "Core/Battle/Actions/ActionContext.hpp"
#include "Core/Units/UnitId.hpp"
#include "GameTime.hpp"
#include "Managers/IGameContinuationChecker.hpp"
#include "Managers/IMapManager.hpp"
#include "Managers/IUnitManager.hpp"
#include "Managers/IUnitSpawnValidator.hpp"

#include <algorithm>
#include <functional>
#include <memory>
#include <optional>
#include <random>
#include <utility>
#include <vector>

namespace sw::core
{
	class IEventLogger;
	class Unit;
	struct Position;
	class IMap;
}

namespace sw::core
{
	class GameSimulator
	{
	private:
		std::unique_ptr<IMapManager> mapManager;
		std::unique_ptr<IUnitManager> unitManager;
		IEventLogger* eventLogger;
		GameTime& gameTime;
		std::mt19937 rng;
		std::unique_ptr<IGameContinuationChecker> continuationChecker;
		std::unique_ptr<IUnitSpawnValidator> spawnValidator;

		std::optional<ActionContext> cachedActionContext;

		ActionContext& getActionContext();
		void processTick();

	public:
		explicit GameSimulator(
			IEventLogger& eventLogger,
			GameTime& gameTime = GameTime::getMutableInstance(),
			std::unique_ptr<IGameContinuationChecker> continuationChecker = nullptr);
		~GameSimulator();

		void createMap(
			uint32_t width,
			uint32_t height,
			std::unique_ptr<IUnitManager> unitManager,
			std::unique_ptr<IMapManager> mapManager,
			std::unique_ptr<IUnitSpawnValidator> spawnValidator);
		void setContinuationChecker(std::unique_ptr<IGameContinuationChecker> continuationChecker);
		void spawnUnit(std::unique_ptr<Unit> unit);
		Unit* getUnit(UnitId id) const;
		void setUnitTargetPosition(UnitId id, Position target);
		bool shouldContinue();
		void simulate();
	};
}
