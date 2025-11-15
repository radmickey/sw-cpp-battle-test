#pragma once

#include "Core/Units/Components/Health/IHealth.hpp"

namespace sw::features
{
	class DefaultHealth : public sw::core::IHealth
	{
	private:
		bool hasHpFlag;
		int currentHp;

	public:
		DefaultHealth(bool hasHp, int initialHp = 0);

		int getHp() const override;
		bool hasHp() const override;
		void setHp(int hp) override;
		void takeDamage(int damage) override;
		bool isAlive() const override;
	};
}

