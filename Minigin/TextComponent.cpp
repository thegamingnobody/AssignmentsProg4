#include <stdexcept>
#include <SDL_ttf.h>
#include "TextComponent.h"
#include "Renderer.h"

#include "Font.h"
#include "Texture2D.h"
#include "TextureComponent.h"
#include "GameObject.h"

void dae::TextComponent::Update(float const)
{
	if (m_needsUpdate)
	{
		const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);

		auto owner{ GetOwner() };
		owner->GetComponent<TextureComponent>().SetTexture(std::make_shared<Texture2D>(texture));
		m_needsUpdate = false;
	}
}

void dae::TextComponent::SetText(const std::string& newText)
{
	m_text = newText; 
	m_needsUpdate = true;
}

dae::TextComponent::TextComponent(dae::GameObject* object, const std::string& text, std::shared_ptr<Font> font) : Component(object),
	m_needsUpdate(true), 
	m_text(text), 
	m_font(std::move(font))
{
}