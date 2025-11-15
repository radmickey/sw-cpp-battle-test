#pragma once

namespace sw::core
{
	struct UnitProperties
	{
		bool canMove;
		bool hasHp;
		bool isFlying;
		bool occupiesCell;
		int initialHp;

		UnitProperties(
			bool canMove = true,
			bool hasHp = true,
			bool isFlying = false,
			bool occupiesCell = true,
			int initialHp = 0) :
				canMove(canMove),
				hasHp(hasHp),
				isFlying(isFlying),
				occupiesCell(occupiesCell),
				initialHp(initialHp)
		{}
	};
}
