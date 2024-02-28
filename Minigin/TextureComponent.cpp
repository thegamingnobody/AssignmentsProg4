#include "TextureComponent.h"
#include "ResourceManager.h"
#include <iostream>
#include "Renderer.h"


void dae::TextureComponent::Render(float const parentX, float const parentY) const
{
	if (m_Texture != nullptr)
	{
		Renderer::GetInstance().RenderTexture(*m_Texture, parentX, parentY);
	}
}

void dae::TextureComponent::Render(Transform const& transform) const
{
	glm::vec3 const pos{ transform.GetPosition() };
	Render(pos.x, pos.y);
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	try
	{
		auto isValidTexture{ ResourceManager::GetInstance().LoadTexture(filename) };
		m_Texture.reset();
		m_Texture = isValidTexture;
		isValidTexture.reset();
	}
	catch (...)
	{
		std::cout << "Invalid Texture: \"" << filename << "\"\n";
	}
}

void dae::TextureComponent::SetTexture(const std::shared_ptr<Texture2D>& texture)
{
	if (texture)
	{
		m_Texture = texture;
	}
}

dae::TextureComponent::TextureComponent(dae::GameObject* object) : Component(object)
{
}

dae::TextureComponent::TextureComponent(dae::GameObject* object, const std::string& filename) : Component(object)
{
	SetTexture(filename);
}
