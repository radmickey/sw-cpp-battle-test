#pragma once

#include "Core/Battle/Actions/IAction.hpp"
#include "Core/Map/IPosition.hpp"

#include <cstdint>

namespace sw::core
{
	class Unit;
	class IMap;
	class IEventLogger;
	struct ActionCheckContext;
	struct ActionContext;
}

namespace sw::features
{
	using sw::core::IAction;
	using sw::core::ActionCheckContext;
	using sw::core::ActionContext;
	using sw::core::IEventLogger;
	using sw::core::IMap;
	using sw::core::IPosition;
	using sw::core::Unit;

	class Move : public IAction
	{
	private:
		uint32_t moveDistance;

		void updateUnitPosition(
			Unit& actor,
			IMap& map,
			const IPosition& newPos,
			const IPosition& oldPos,
			IEventLogger& logger,
			uint64_t currentTick) const;
		void endMarch(Unit& actor, const IPosition& pos, IEventLogger& logger, uint64_t currentTick) const;

	public:
		explicit Move(uint32_t moveDistance = 1);

		bool canExecute(const Unit& actor, const ActionCheckContext& context) override;
		void execute(Unit& actor, ActionContext& context) override;
	};
}
