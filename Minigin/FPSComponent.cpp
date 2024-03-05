#include "FPSComponent.h"
#include "TextComponent.h"
#include "GameObject.h"

void dae::FPSComponent::Update(float const elapsedTime)
{
	m_FrameCount++;
	m_Delay += elapsedTime;

	if (m_Delay >= m_MaxDelay)
	{
		auto textComponent{ GetOwner()->GetComponent<dae::TextComponent>() };
		if (textComponent.has_value())
		{
			std::stringstream stream;
			stream << std::fixed << std::setprecision(1) << m_FrameCount/m_Delay << " FPS";
			textComponent.value()->SetText(stream.str());
		}

		m_FrameCount = 0;
		m_Delay = 0;
	}
}

dae::FPSComponent::FPSComponent(dae::GameObject* object) : Component(object)
{
}
