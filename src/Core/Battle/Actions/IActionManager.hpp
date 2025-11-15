#pragma once

#include <memory>
#include <vector>

namespace sw::core
{
	class IAction;

	class IActionManager
	{
	public:
		virtual ~IActionManager() = default;

		virtual const std::vector<std::unique_ptr<IAction>>& getActions() const = 0;
		virtual bool hasActions() const = 0;
		virtual void addAction(std::unique_ptr<IAction> action) = 0;
		virtual void clearActions() = 0;
	};
}

