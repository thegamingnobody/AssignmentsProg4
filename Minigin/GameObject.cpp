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

	m_transform.Move(5, 5, 0);
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

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

void dae::GameObject::SetLoopable(bool const loop)
{
	m_transform.SetLoopable(loop);
}
