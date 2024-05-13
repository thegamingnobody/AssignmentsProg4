#include "Transform.h"
#include "Minigin.h"
#include "GameObject.h"
#include "EventManager.h"

void dae::Transform::Update(float const)
{
}

void dae::Transform::Reset()
{
	m_LocalPosition = glm::vec3(0, 0, 0);
	m_ParentWorldPos = glm::vec3(0, 0, 0);
	m_DirectionThisFrame = glm::vec3(0, 0, 0);
}

const glm::vec3& dae::Transform::GetPosition()
{
	bool pushEvent{ false };

	//Is true when parent pos changed or local pos changed outside of this function
	if (m_ShouldUpdate)
	{
		m_ShouldUpdate = false;

		//update position locally
		if (m_DirectionThisFrame.x != 0.0f or m_DirectionThisFrame.y != 0.0f or m_DirectionThisFrame.z != 0.0f)
		{
			m_WorldPosition += glm::normalize(m_DirectionThisFrame);
			m_DirectionThisFrame = glm::vec3(0, 0, 0);
			pushEvent = true;
		}

		//parentworldpos should always be zero if no parent => should be safe
		m_WorldPosition += (m_ParentWorldPos + m_LocalPosition);
		pushEvent = true;			
	}

	if (pushEvent)
	{
		auto owner{ GetOwner() };
		std::tuple<const dae::GameObject*, const glm::vec3&> eventTuple{ owner, m_WorldPosition };
		Event eventToPush{ EventType::TransformChanged, eventTuple, GetOwner()->m_PlayerNumber };
		dae::EventManager::GetInstance().PushEvent(eventToPush);
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

void dae::Transform::Move(float const addedX, float const addedY, float const addedZ)
{
	m_ShouldUpdate = true;

	m_DirectionThisFrame.x += addedX;
	m_DirectionThisFrame.y += addedY;
	m_DirectionThisFrame.z += addedZ;
}

dae::Transform::Transform(dae::GameObject* object) 
	: Component(object)
	, m_ShouldUpdate(false)
	, m_LocalPosition(glm::vec3(0, 0, 0))
	, m_WorldPosition(glm::vec3(0, 0, 0))
	, m_DirectionThisFrame(glm::vec3(0, 0, 0))
	, m_ParentWorldPos(glm::vec3(0, 0, 0))
{
	m_TargetNumber = object->m_PlayerNumber;
	dae::EventManager::GetInstance().AddObserver(this, dae::EventType::MoveObject);
	dae::EventManager::GetInstance().AddObserver(this, dae::EventType::TransformChanged);
}

dae::Transform::Transform(dae::GameObject* object, float const x, float const y, float const z) 
	: Component(object)
	, m_ShouldUpdate(false)
	, m_LocalPosition(glm::vec3(0, 0, 0))
	, m_WorldPosition(glm::vec3(x, y, z))
	, m_DirectionThisFrame(glm::vec3(0, 0, 0))
	, m_ParentWorldPos(glm::vec3(0, 0, 0))
{
	m_TargetNumber = object->m_PlayerNumber;

	dae::EventManager::GetInstance().AddObserver(this, dae::EventType::MoveObject);
	dae::EventManager::GetInstance().AddObserver(this, dae::EventType::TransformChanged);
}

void dae::Transform::Notify(const Event& event)
{
	switch (event.m_type)
	{
	case dae::EventType::MoveObject:
		{
			auto castedArguments{ std::get<0>(event.GetArgumentsAsTuple<const glm::vec3&>()) };
			Move(castedArguments.x, castedArguments.y, castedArguments.z);
		}
		break;
	case dae::EventType::TransformChanged:
		{
			auto castedArguments{ event.GetArgumentsAsTuple<const dae::GameObject*, const glm::vec3&>() };
			auto owner = GetOwner();
			auto ownerParent = owner->GetParent();
			
			if (not ownerParent.has_value()) break;

			if (ownerParent.value() == std::get<0>(castedArguments) and ownerParent.value()->HasChildren())
			{
				m_ShouldUpdate = true;
				m_ParentWorldPos = std::get<1>(castedArguments);
			}
		}
		break;
	default:
		break;
	}
}
