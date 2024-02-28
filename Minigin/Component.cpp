#include "Component.h"

dae::Component::Component(dae::GameObject* object) :
	m_pGameObject(object)
{
}

void dae::Component::Update(float const)
{
}

dae::GameObject* dae::Component::GetOwner() const
{
	return m_pGameObject;
}
