#pragma once

#include <cstdint>
#include <functional>
#include <random>

namespace sw::core
{
	class Unit;
	class IMap;
	class IEventLogger;
	struct Position;
	struct ActionContext;
	struct ActionCheckContext;
}

namespace sw::core
{
	class Action
	{
	protected:
		void performAttack(Unit& actor, Unit* target, int damage, IEventLogger& logger, uint64_t currentTick);

	public:
		virtual ~Action() = default;

		virtual bool canExecute(const Unit& actor, const ActionCheckContext& context) = 0;
		virtual void execute(Unit& actor, ActionContext& context) = 0;
	};
}
