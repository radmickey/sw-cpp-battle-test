#pragma once

#include <cstdint>

namespace sw::core
{
	class GameTime
	{
	private:
		uint64_t currentTick;
		static GameTime* instance;

		GameTime();

	public:
		explicit GameTime(uint64_t initialTick);
		GameTime(const GameTime&) = delete;
		GameTime& operator=(const GameTime&) = delete;

		static const GameTime& getInstance();
		static GameTime& getMutableInstance();
		static void resetInstance();

		uint64_t getCurrentTick() const;
		void nextTick();
		void reset();
		void setTick(uint64_t tick);
	};
}
