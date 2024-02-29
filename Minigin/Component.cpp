#include "Component.h"

dae::Component::Component(dae::GameObject* object) :
	m_pGameObject(object)
{
}

void dae::Component::Update(float const)
{
}

void dae::Component::SetShouldBeRemoved()
{
	m_ShouldBeRemoved = true;
}

dae::GameObject* dae::Component::GetOwner() const
{
	return m_pGameObject;
}
