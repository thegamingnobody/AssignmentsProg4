#include "TextureComponent.h"
#include "ResourceManager.h"
#include <iostream>
#include "Renderer.h"
#include "Transform.h"
#include "GameObject.h"


void dae::TextureComponent::Render() const
{
	if (m_Texture != nullptr)
	{
		try
		{
			auto& transformComp{ GetOwner()->GetComponent<dae::Transform>() };
			auto& pos{ transformComp.GetPosition() };
			Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
		}
		catch (...)
		{
			Renderer::GetInstance().RenderTexture(*m_Texture, 0.0f, 0.0f);
		}

	}
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
