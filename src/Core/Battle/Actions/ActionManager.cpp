#include "ActionManager.hpp"

#include "Action.hpp"

namespace sw::core
{
	const std::vector<std::unique_ptr<Action>>& ActionManager::getActions() const
	{
		return actions;
	}

	bool ActionManager::hasActions() const
	{
		return !actions.empty();
	}

	void ActionManager::addAction(std::unique_ptr<Action> action)
	{
		actions.push_back(std::move(action));
	}

	void ActionManager::clearActions()
	{
		actions.clear();
	}
}
