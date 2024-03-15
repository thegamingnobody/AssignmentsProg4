#include "Action.h"

dae::Action::Action(const Controller::Buttons& controllerButton, std::shared_ptr<Command> command, int const playerNumber) :
	m_PlayerNumber		(playerNumber),
	m_ControllerInput	(controllerButton),
	m_KeyboardInput		(),
	m_Command			(command),
	m_InputMode			(InputMode::Controller)
{
}

dae::Action::Action(const Keyboard::Buttons& keyboardKey, std::shared_ptr<Command> command, int const playerNumber) :
	m_PlayerNumber		(playerNumber),
	m_ControllerInput	(),
	m_KeyboardInput		(keyboardKey),
	m_Command			(command),
	m_InputMode			(InputMode::Keyboard)
{
}

void dae::Action::Execute()
{
	m_Command->Execute();
}
