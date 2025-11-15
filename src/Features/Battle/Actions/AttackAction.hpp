#pragma once

#include "Core/Battle/Actions/IAction.hpp"

#include <cstdint>

namespace sw::core
{
	class Unit;
	class IEventLogger;
}

namespace sw::features
{
	class AttackAction : public sw::core::IAction
	{
	protected:
		void performAttack(sw::core::Unit& actor, sw::core::Unit* target, int damage, sw::core::IEventLogger& logger, uint64_t currentTick);
	};
}

