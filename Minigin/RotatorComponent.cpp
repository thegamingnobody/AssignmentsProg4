#include "RotatorComponent.h"
#include "GameObject.h"

void dae::RotatorComponent::Update(float const elapsedTime)
{
	auto owner{ GetOwner() };

	m_Angle += (m_Speed / 360) * elapsedTime;
	owner->SetPosition(m_Center.GetPosition().x + (cosf(m_Angle) * m_Radius), m_Center.GetPosition().y - (sinf(m_Angle) * m_Radius));
}

dae::RotatorComponent::RotatorComponent(dae::GameObject* object) : Component(object)
{
	m_Center = object->GetTransform();
}
