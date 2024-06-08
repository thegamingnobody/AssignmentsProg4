#include "BoundingBoxComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "EventManager.h"
#include "CollisionManager.h"


dae::BoundingBoxComponent::BoundingBoxComponent(dae::GameObject* object, float const width, float const height)
	: Component(object)
	, m_BoundingBox()
	, m_BoxId(0)
	, m_MovedThisFrame(false)
{
	m_TargetNumber = object->m_PlayerNumber;

	m_BoundingBox.x = 0;
	m_BoundingBox.y = 0;
	m_BoundingBox.width = width;
	m_BoundingBox.height = height;
	dae::EventManager::GetInstance().AddObserver(this, dae::EventType::TransformChanged);
	dae::CollisionManager::GetInstance().RegisterBB(this);
}

void dae::BoundingBoxComponent::Notify(const Event& event)
{
	switch (event.m_type)
	{
	case dae::EventType::TransformChanged:
		{
			auto castedArguments{ event.GetArgumentsAsTuple<const dae::GameObject*, const glm::vec3&>() };

			if (GetOwner() == std::get<0>(castedArguments))
			{
				m_BoundingBox.x = std::get<1>(castedArguments).x;
				m_BoundingBox.y = std::get<1>(castedArguments).y;
				m_MovedThisFrame = true;
			}
		}
		break;
	default:
		break;
	}
}

dae::Rect& dae::BoundingBoxComponent::GetBoundingBox()
{
	return m_BoundingBox;
}

void dae::BoundingBoxComponent::ResetDirectionThisFrame(bool const resetX, bool const resetY)
{
	auto transformComponent = GetOwner()->GetComponent<Transform>();

	if (transformComponent.has_value())
	{
		transformComponent.value()->ResetDirection(resetX, resetY);
	}
}
