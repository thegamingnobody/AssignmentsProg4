#include <SDL.h>
#include "InputManager.h"
#include <backends/imgui_impl_sdl2.h>

bool dae::InputManager::ProcessInput()
{
	for (auto& inputDevice : m_InputDevices)
	{
		inputDevice->Update();
	}

	for (auto& action : m_Actions)
	{
		for (auto& inputDevice : m_InputDevices)
		{
			if (inputDevice->GetPlayerNumber() != action->GetPlayerNumber()) continue;

			if (inputDevice->IsButtonPressed(action->GetButton()))
			{
				action->Execute();
			}
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
	int const newPlayerNumber{ static_cast<int>(m_InputDevices.size()) };

	switch (inputMode)
	{
	case Action::InputMode::Controller:
		m_InputDevices.emplace_back(std::make_unique<Controller>(newPlayerNumber));
		break;
	case Action::InputMode::Keyboard:
		m_InputDevices.emplace_back(std::make_unique<Keyboard>(newPlayerNumber));
		break;
	default:
		break;
	}

	return newPlayerNumber;
}

std::shared_ptr<dae::Action> dae::InputManager::AddAction(const ControllerButtons& controllerButton, std::shared_ptr<Command> command, int const playerNumber)
{
	std::shared_ptr<Action> action = std::make_shared<Action>(controllerButton, command, playerNumber);
	m_Actions.emplace_back(action);
	return action;
}

std::shared_ptr<dae::Action> dae::InputManager::AddAction(const KeyboardKeys& keyboardKey, std::shared_ptr<Command> command, int const playerNumber)
{
	std::shared_ptr<Action> action = std::make_shared<Action>(keyboardKey, command, playerNumber);
	m_Actions.emplace_back(action);
	return action;
}
