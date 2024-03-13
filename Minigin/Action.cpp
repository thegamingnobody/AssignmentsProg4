#include "Action.h"

dae::Action::Action(Controller::Buttons controllerButton, std::shared_ptr<Command> command, int const controllerIndex) :
	m_ControllerInput(controllerButton),
	m_Command(command),
	m_ControllerIndex(controllerIndex)
{
}

void dae::Action::Execute()
{
	m_Command->Execute();
}
