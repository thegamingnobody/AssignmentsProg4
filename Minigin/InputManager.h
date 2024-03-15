#pragma once
#include "Singleton.h"
#include <vector>
#include <memory>
#include "Controller.h"
#include "Keyboard.h"
#include "Action.h"


namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		
		int AddController(const Action::InputMode& inputMode);
		std::shared_ptr<Action> AddAction(const Controller::Buttons& controllerButton, std::shared_ptr<Command> command, int const playerNumber);
		std::shared_ptr<Action> AddAction(const Keyboard::Buttons& keyboardKey, std::shared_ptr<Command> command, int const playerNumber);

	private:
		std::vector<std::unique_ptr<Controller>> m_Controllers;
		std::vector<std::unique_ptr<Keyboard>> m_Keyboards;
		std::vector<std::shared_ptr<Action>> m_Actions;
	};

}
