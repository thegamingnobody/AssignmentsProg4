#include "MoveCommand.h"
#include "EventManager.h"


dae::MoveCommand::MoveCommand(int const playerNumber, glm::vec3 direction) :
	m_Direction(direction)
{
	m_PlayerNumber = playerNumber;
}

void dae::MoveCommand::Execute()
{
	//m_TransformComponent.value()->Move(m_Direction.x, m_Direction.y, m_Direction.z);
	std::tuple<const glm::vec3&> eventArguments{m_Direction};
	Event eventToNotify{ dae::EventType::MoveObject, eventArguments, m_PlayerNumber };

	dae::EventManager::GetInstance().PushEvent(eventToNotify);
}
