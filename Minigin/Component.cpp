#include "Component.h"

Component::Component(std::weak_ptr<dae::GameObject> object) :
	m_pGameObject(object)
{
}

void Component::Update(float const)
{
}

void Component::Render() const
{
}

dae::GameObject* Component::GetOwner() const
{
	return m_pGameObject.lock().get();
}
