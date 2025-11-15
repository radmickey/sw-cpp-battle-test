#include "GameTime.hpp"

namespace sw::core
{
	GameTime* GameTime::instance = nullptr;

	GameTime::GameTime() :
			currentTick(1)
	{}

	GameTime::GameTime(uint64_t initialTick) :
			currentTick(initialTick)
	{}

	const GameTime& GameTime::getInstance()
	{
		if (!instance)
		{
			instance = new GameTime();
		}
		return *instance;
	}

	GameTime& GameTime::getMutableInstance()
	{
		if (!instance)
		{
			instance = new GameTime();
		}
		return *instance;
	}

	void GameTime::resetInstance()
	{
		if (instance)
		{
			delete instance;
			instance = nullptr;
		}
	}

	uint64_t GameTime::getCurrentTick() const
	{
		return currentTick;
	}

	void GameTime::nextTick()
	{
		++currentTick;
	}

	void GameTime::reset()
	{
		currentTick = 1;
	}

	void GameTime::setTick(uint64_t tick)
	{
		currentTick = tick;
	}
}
