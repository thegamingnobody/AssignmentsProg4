#include <SDL.h>
#include "InputManager.h"
#include <backends/imgui_impl_sdl2.h>

bool dae::InputManager::ProcessInput()
{
	for (auto& controller : m_Controllers)
	{
		controller->Update();
	}

	for (auto& keyboard : m_Keyboards)
	{
		keyboard->Update();
	}

	for (auto& action : m_Actions)
	{
		switch (action->GetInputMode())
		{
		case Action::InputMode::Controller:
			for (auto& controller : m_Controllers)
			{
				if (controller->GetPlayerNumber() != action->GetPlayerNumber()) continue;

				if (controller->IsButtonPressed(action->GetButton()))
				{
					action->Execute();
				}
			}
			break;
		case Action::InputMode::Keyboard:
			for (auto& keyboard : m_Keyboards)
			{
				if (keyboard->GetKeyboardIndex() != action->GetPlayerNumber()) continue;

				if (keyboard->IsButtonPressed(action->GetKey()))
				{
					action->Execute();
				}
			}
			break;
		default:
			break;
		}


	}

	SDL_Event e;
	while (SDL_PollEvent(&e)) 
	{
		if (e.type == SDL_QUIT) 
		{
			return false;
		}

		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	return true;
}

int dae::InputManager::AddController(const Action::InputMode& inputMode)
{
	int newPlayerNumber{};
	switch (inputMode)
	{
	case Action::InputMode::Controller:
		newPlayerNumber = static_cast<int>(m_Controllers.size());
		m_Controllers.emplace_back(std::make_unique<Controller>(newPlayerNumber));
		break;
	case Action::InputMode::Keyboard:
		newPlayerNumber = static_cast<int>(m_Keyboards.size());
		m_Keyboards.emplace_back(std::make_unique<Keyboard>(newPlayerNumber));
		break;
	default:
		break;
	}

	return newPlayerNumber;
}

std::shared_ptr<dae::Action> dae::InputManager::AddAction(const Controller::Buttons& controllerButton, std::shared_ptr<Command> command, int const playerNumber)
{
	std::shared_ptr<Action> action = std::make_shared<Action>(controllerButton, command, playerNumber);
	m_Actions.emplace_back(action);
	return action;
}

std::shared_ptr<dae::Action> dae::InputManager::AddAction(const Keyboard::Buttons& keyboardKey, std::shared_ptr<Command> command, int const playerNumber)
{
	std::shared_ptr<Action> action = std::make_shared<Action>(keyboardKey, command, playerNumber);
	m_Actions.emplace_back(action);
	return action;
}
