#include "RotatorComponent.h"
#include "GameObject.h"

void dae::RotatorComponent::Update(float const elapsedTime)
{
	auto owner{ GetOwner() };

	m_Angle += (m_Speed / 360) * elapsedTime;

	auto transformComp{ owner->GetComponent<Transform>() };

	if (transformComp.has_value())
	{
		transformComp.value()->SetPosition((cosf(m_Angle) * m_Radius), -(sinf(m_Angle) * m_Radius));
	}
}

dae::RotatorComponent::RotatorComponent(dae::GameObject* object, float const speed, float const radius) : Component(object)
{
	m_Speed = speed;
	m_Radius = radius;
}
