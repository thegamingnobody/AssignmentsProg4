#include "MoveCommand.h"

dae::MoveCommand::MoveCommand(dae::GameObject* actor) :
	m_Actor(actor)
{
}

void dae::MoveCommand::Execute()
{
	std::cout << "move\n";
}
