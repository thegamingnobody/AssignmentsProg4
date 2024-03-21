#include "MoveCommand.h"

dae::MoveCommand::MoveCommand(dae::GameObject* actor, glm::vec3 direction) :
	m_Actor(actor),
	m_Direction(direction)
{
	m_TransformComponent = actor->GetComponent<dae::Transform>();
	assert(m_TransformComponent.has_value());
}

void dae::MoveCommand::Execute()
{
	m_TransformComponent.value()->Move(m_Direction.x, m_Direction.y, m_Direction.z);
}
