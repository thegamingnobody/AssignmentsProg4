#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TextComponent.h"

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

		if (auto derivedComponent = dynamic_cast<dae::TextComponent*>(component.get()))
		{
			m_texture.reset();
			m_texture = component->GetTexture();
		}
	}
}

void dae::GameObject::Render() const
{
	if (not m_Render) return;

	const auto& pos = m_transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}