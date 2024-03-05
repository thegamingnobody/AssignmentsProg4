#include "Transform.h"
#include "Minigin.h"
#include "GameObject.h"

void dae::Transform::Update(float const)
{
	try
	{
		dae::GameObject* ParentOfOwner{};
		if (GetOwner()->HasParent())
		{
			ParentOfOwner = GetOwner()->GetParent();
			auto& ParentOfOwnerPos{ ParentOfOwner->GetComponent<dae::Transform>().GetPosition() };
			if (ParentOfOwnerPos + m_LocalPosition != m_WorldPosition)
			{
				m_ShouldUpdate = true;
			}
		}
	}
	catch (...)
	{
		//no error handling needed, if object doesn't have parent or parent of ownerObject has no transform, then local transform is its world transform
	}
}

void dae::Transform::Reset()
{
	m_LocalPosition.x = 0.0f;
	m_LocalPosition.y = 0.0f;
	m_LocalPosition.z = 0.0f;
}

const glm::vec3& dae::Transform::GetPosition()
{
	if (m_ShouldUpdate)
	{
		m_ShouldUpdate = false;

		try
		{
			auto& ParentOfOwnerPos{ GetOwner()->GetParent()->GetComponent<dae::Transform>().GetPosition() };
			m_WorldPosition = (ParentOfOwnerPos + m_LocalPosition);
			return m_WorldPosition;
		}
		catch (...)
		{
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

	if (m_Loop)
	{
		m_LocalPosition.x = static_cast<float>(static_cast<int>(m_LocalPosition.x + addedX) % dae::Minigin::m_WindowWidth);
		m_LocalPosition.y = static_cast<float>(static_cast<int>(m_LocalPosition.y + addedY) % dae::Minigin::m_WindowHeight);
	}
	else
	{
		m_LocalPosition.x += addedX;
		m_LocalPosition.y += addedY;
	}
	m_LocalPosition.z += addedZ;
}

dae::Transform::Transform(dae::GameObject* object) : Component(object),
	m_LocalPosition()
{
}

dae::Transform::Transform(dae::GameObject* object, float const x, float const y, float const z) : Component(object)
{
	SetPosition(x, y, z);
}