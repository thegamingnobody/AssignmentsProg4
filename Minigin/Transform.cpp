#include "Transform.h"
#include "Minigin.h"
#include "GameObject.h"

void dae::Transform::Update(float const)
{

	auto ParentOfOwner{ GetOwner()->GetParent() };
	if (not ParentOfOwner.has_value()) return;

	auto TransformComponent{ ParentOfOwner.value()->GetComponent<dae::Transform>()};
	if (not TransformComponent.has_value()) return;

	if (TransformComponent.value()->GetPosition() + m_LocalPosition != m_WorldPosition)
	{
		m_ShouldUpdate = true;
	}
}

void dae::Transform::Reset()
{
	m_LocalPosition = glm::vec3(0, 0, 0);
	m_DirectionThisFrame = glm::vec3(0, 0, 0);
}

const glm::vec3& dae::Transform::GetPosition()
{
	if (m_ShouldUpdate)
	{
		m_ShouldUpdate = false;

		if (not(m_DirectionThisFrame.x == 0.0f and m_DirectionThisFrame.y == 0.0f and m_DirectionThisFrame.z == 0.0f))
		{
			m_LocalPosition += glm::normalize(m_DirectionThisFrame);
			m_DirectionThisFrame = glm::vec3(0, 0, 0);
		}

		auto ParentOfOwner{ GetOwner()->GetParent() };
		if (ParentOfOwner.has_value())
		{
			auto TransformComponent{ ParentOfOwner.value()->GetComponent<dae::Transform>() };

			if (TransformComponent.has_value())
			{
				m_WorldPosition = (TransformComponent.value()->GetPosition() + m_LocalPosition);
				return m_WorldPosition;
			}			
		}
		else
		{
			m_WorldPosition = m_LocalPosition;
			m_WorldPosition = m_LocalPosition;
			return m_LocalPosition;
		}
	}

	return m_WorldPosition;
}

void dae::Transform::SetPosition(float const x, float const y, float const z)
{
	m_LocalPosition.x = x;
	m_LocalPosition.y = y;
	m_LocalPosition.z = z;
	m_ShouldUpdate = true;
}

void dae::Transform::SetLoopable(bool const loop)
{
	m_Loop = loop;
}

void dae::Transform::Move(float const addedX, float const addedY, float const addedZ)
{
	m_ShouldUpdate = true;

	m_DirectionThisFrame.x += addedX;
	m_DirectionThisFrame.y += addedY;
	m_DirectionThisFrame.z += addedZ;

	//if (m_Loop)
	//{
	//	m_LocalPosition.x = static_cast<float>(static_cast<int>(m_LocalPosition.x + addedX) % dae::Minigin::m_WindowWidth);
	//	m_LocalPosition.y = static_cast<float>(static_cast<int>(m_LocalPosition.y + addedY) % dae::Minigin::m_WindowHeight);
	//}
	//else
	//{
	//	m_LocalPosition.x += addedX;
	//	m_LocalPosition.y += addedY;
	//}
	//m_LocalPosition.z += addedZ;
}

dae::Transform::Transform(dae::GameObject* object) : Component(object)
	, m_LocalPosition()
	, m_WorldPosition()
	, m_DirectionThisFrame()
{
}

dae::Transform::Transform(dae::GameObject* object, float const x, float const y, float const z) : Component(object)
{
	SetPosition(x, y, z);
}