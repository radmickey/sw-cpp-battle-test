#pragma once

#include "Core/Battle/Actions/IActionManager.hpp"

#include <memory>
#include <vector>

namespace sw::core
{
	class IAction;
}

namespace sw::features
{
	class DefaultActionManager : public sw::core::IActionManager
	{
	private:
		std::vector<std::unique_ptr<sw::core::IAction>> actions;

	public:
		const std::vector<std::unique_ptr<sw::core::IAction>>& getActions() const override;
		bool hasActions() const override;
		void addAction(std::unique_ptr<sw::core::IAction> action) override;
		void clearActions() override;
	};
}

