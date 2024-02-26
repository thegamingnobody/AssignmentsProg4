#include "Component.h"

Component::Component(std::shared_ptr<dae::GameObject> object) :
	m_pGameObject(object)
{
}

void Component::Update(float const)
{
}

void Component::Render() const
{
}

void Component::SetOwnerObject(std::shared_ptr<dae::GameObject> object)
{
	m_pGameObject.reset();
	m_pGameObject = object;
}

std::shared_ptr<dae::GameObject> Component::GetOwner() const
{
	return m_pGameObject;
}
