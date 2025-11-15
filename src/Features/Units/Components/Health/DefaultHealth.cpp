#include "DefaultHealth.hpp"

namespace sw::features
{
	DefaultHealth::DefaultHealth(bool hasHp, int initialHp) :
			hasHpFlag(hasHp),
			currentHp(hasHp ? initialHp : 0)
	{}

	int DefaultHealth::getHp() const
	{
		return hasHpFlag ? currentHp : 0;
	}

	bool DefaultHealth::hasHp() const
	{
		return hasHpFlag;
	}

	void DefaultHealth::setHp(int hp)
	{
		if (hasHpFlag)
		{
			currentHp = hp;
		}
	}

	void DefaultHealth::takeDamage(int damage)
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

	bool DefaultHealth::isAlive() const
	{
		return !hasHpFlag || currentHp > 0;
	}
}

