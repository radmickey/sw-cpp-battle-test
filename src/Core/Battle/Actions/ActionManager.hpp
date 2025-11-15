#pragma once

#include <memory>
#include <vector>

namespace sw::core
{
	class Action;
}

namespace sw::core
{
	class ActionManager
	{
	private:
		std::vector<std::unique_ptr<Action>> actions;

	public:
		const std::vector<std::unique_ptr<Action>>& getActions() const;
		bool hasActions() const;
		void addAction(std::unique_ptr<Action> action);
		void clearActions();
	};
}
