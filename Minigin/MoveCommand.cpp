#include "MoveCommand.h"

dae::MoveCommand::MoveCommand(dae::GameObject* actor, glm::vec3 direction) :
	m_Actor(actor),
	m_Direction(direction)
{
}

void dae::MoveCommand::Execute()
{
	auto transformComponent{ m_Actor->GetComponent<dae::Transform>() };

	if (transformComponent.has_value())
	{
		transformComponent.value()->Move(m_Direction.x, m_Direction.y, m_Direction.z);
	}
	else
	{
		throw std::runtime_error("No Transform Component found");
	}

}
