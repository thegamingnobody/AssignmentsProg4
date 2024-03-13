#pragma once
#include "Singleton.h"
#include <vector>
#include <memory>
#include "Controller.h"
#include "Action.h"


namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		
		int AddController();
		std::shared_ptr<Action> AddAction(Controller::Buttons controllerButton, std::shared_ptr<Command> command, int const controllerIndex);

	private:
		std::vector<std::unique_ptr<Controller>> m_Controllers;
		std::vector<std::shared_ptr<Action>> m_Actions;
	};

}
