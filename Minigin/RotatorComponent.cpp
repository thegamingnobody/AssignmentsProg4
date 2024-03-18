#include "RotatorComponent.h"
#include "GameObject.h"

void dae::RotatorComponent::Update(float const elapsedTime)
{
	m_Angle += (m_Speed / 360) * elapsedTime;

	if (m_OwnerTransformComponent.has_value())
	{
		m_OwnerTransformComponent.value()->SetPosition((cosf(m_Angle) * m_Radius), -(sinf(m_Angle) * m_Radius));
	}
}

dae::RotatorComponent::RotatorComponent(dae::GameObject* object, float const speed, float const radius) : Component(object)
{
	m_Speed = speed;
	m_Radius = radius;
	m_OwnerTransformComponent = object->GetComponent<Transform>();
}
