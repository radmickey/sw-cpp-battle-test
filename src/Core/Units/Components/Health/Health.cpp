#include "Health.hpp"

namespace sw::core
{
	Health::Health(bool hasHp, int initialHp) :
			hasHpFlag(hasHp),
			currentHp(hasHp ? initialHp : 0)
	{}

	int Health::getHp() const
	{
		return hasHpFlag ? currentHp : 0;
	}

	bool Health::hasHp() const
	{
		return hasHpFlag;
	}

	void Health::setHp(int hp)
	{
		if (hasHpFlag)
		{
			currentHp = hp;
		}
	}

	void Health::takeDamage(int damage)
	{
		if (hasHpFlag)
		{
			currentHp -= damage;
			if (currentHp < 0)
			{
				currentHp = 0;
			}
		}
	}

	bool Health::isAlive() const
	{
		return !hasHpFlag || currentHp > 0;
	}
}
