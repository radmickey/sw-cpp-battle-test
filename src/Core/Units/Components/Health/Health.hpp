#pragma once

namespace sw::core
{
	class Health
	{
	private:
		bool hasHpFlag;
		int currentHp;

	public:
		Health(bool hasHp, int initialHp = 0);

		int getHp() const;
		bool hasHp() const;
		void setHp(int hp);
		void takeDamage(int damage);
		bool isAlive() const;
	};
}
