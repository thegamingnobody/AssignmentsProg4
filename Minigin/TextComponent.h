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

		void SetText(const std::string& newText);
		std::string& GetText() { return m_text; }

		TextComponent(dae::GameObject* object, const std::string& text, std::shared_ptr<Font> font);
		virtual ~TextComponent() override = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator= (const TextComponent & other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

	private:
		bool m_needsUpdate;
		std::string m_text{};
		std::shared_ptr<Font> m_font;
	};
}

#endif