#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TextComponent.h"
#include "TextureComponent.h"

dae::GameObject::GameObject(bool const renderable)
{
	m_Render = renderable;
}

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(float const elapsedTime)
{
	for (auto& component : m_pComponents)
	{
		component->Update(elapsedTime);
	}

	for (auto it{ m_pComponents.begin() }; it != m_pComponents.end(); it)
	{
		if ((*it)->GetSouldBeRemoved())
		{
			it = m_pComponents.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void dae::GameObject::Render() const
{
	if (not m_Render) return;

	for (auto& component : m_pComponents)
	{
		if (auto derivedComponent = dynamic_cast<dae::TextureComponent*>(component.get()))
		{
			derivedComponent->Render(m_transform);
		}
	}
}

void dae::GameObject::Move(const Transform& addedPosition)
{
	Move(addedPosition.GetPosition().x, addedPosition.GetPosition().y);
}

void dae::GameObject::Move(float const addedX, float const addedY)
{
	m_transform.Move(addedX, addedY, 0);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

void dae::GameObject::SetLoopable(bool const loop)
{
	m_transform.SetLoopable(loop);
}
