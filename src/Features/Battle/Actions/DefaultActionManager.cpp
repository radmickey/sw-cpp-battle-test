#include "DefaultActionManager.hpp"

#include "Core/Battle/Actions/IAction.hpp"

namespace sw::features
{
	const std::vector<std::unique_ptr<sw::core::IAction>>& DefaultActionManager::getActions() const
	{
		return actions;
	}

	bool DefaultActionManager::hasActions() const
	{
		return !actions.empty();
	}

	void DefaultActionManager::addAction(std::unique_ptr<sw::core::IAction> action)
	{
		actions.push_back(std::move(action));
	}

	void DefaultActionManager::clearActions()
	{
		actions.clear();
	}
}

