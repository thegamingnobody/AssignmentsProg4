#include "Action.h"

dae::Action::Action(const ControllerButtons& controllerButton, std::shared_ptr<Command> command, int const playerNumber) :
	m_PlayerNumber		(playerNumber),
	m_ButtonValue		(static_cast<int>(controllerButton)),
	m_Command			(command),
	m_InputMode			(DeviceType::Controller)
{
}

dae::Action::Action(const KeyboardKeys& keyboardKey, std::shared_ptr<Command> command, int const playerNumber) :
	m_PlayerNumber		(playerNumber),
	m_ButtonValue		(static_cast<int>(keyboardKey)),
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
	return m_ButtonValue;
}
