#include "Action.h"

dae::Action::Action(const ControllerButtons& controllerButton, std::shared_ptr<Command> command, int const playerNumber) :
	m_PlayerNumber		(playerNumber),
	m_ControllerInput	(controllerButton),
	m_KeyboardInput		(),
	m_Command			(command),
	m_InputMode			(DeviceType::Controller)
{
}

dae::Action::Action(const KeyboardKeys& keyboardKey, std::shared_ptr<Command> command, int const playerNumber) :
	m_PlayerNumber		(playerNumber),
	m_ControllerInput	(),
	m_KeyboardInput		(keyboardKey),
	m_Command			(command),
	m_InputMode			(DeviceType::Keyboard)
{
}

void dae::Action::Execute()
{
	m_Command->Execute();
}

int dae::Action::GetButton() const
{
	switch (m_InputMode)
	{
	case dae::Action::DeviceType::Controller:
		return static_cast<int>(m_ControllerInput);
	case dae::Action::DeviceType::Keyboard:
		return static_cast<int>(m_KeyboardInput);
	default:
		break;
	}
	return 0;
}
