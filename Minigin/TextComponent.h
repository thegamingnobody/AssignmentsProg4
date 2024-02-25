#ifndef TEXTCOMPONENT
#define TEXTCOMPONENT

#include "Component.h"
#include <string>
#include "Transform.h"

namespace dae
{
	class Font;
	class Texture2D;
	class TextComponent : public Component
	{
	public:
		void Update(float const elapsedTime) override;
		void Render() const override;

		void SetPosition(float x, float y) { m_transform.SetPosition(x, y, 0.0f); }

		void SetText(std::string& newText);
		std::string& GetText() { return m_text; }

		std::shared_ptr<Texture2D> GetTexture() override { return m_textTexture; }

		TextComponent(const std::string& text, std::shared_ptr<Font> font);
		virtual ~TextComponent() override = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator= (const TextComponent & other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

	private:
		bool m_needsUpdate;
		std::string m_text{};
		Transform m_transform{};
		std::shared_ptr<Font> m_font;
		std::shared_ptr<Texture2D> m_textTexture;
	};
}

#endif