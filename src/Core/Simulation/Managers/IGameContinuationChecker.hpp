#pragma once

namespace sw::core
{
	class IGameContinuationChecker
	{
	public:
		virtual ~IGameContinuationChecker() = default;
		virtual bool shouldContinue() const = 0;
	};
}
