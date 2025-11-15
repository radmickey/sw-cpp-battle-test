#pragma once

namespace sw::core
{
	class IHealth
	{
	public:
		virtual ~IHealth() = default;

		virtual int getHp() const = 0;
		virtual bool hasHp() const = 0;
		virtual void setHp(int hp) = 0;
		virtual void takeDamage(int damage) = 0;
		virtual bool isAlive() const = 0;
	};
}

