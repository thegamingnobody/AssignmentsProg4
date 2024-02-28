#include "FPSComponent.h"
#include "TextComponent.h"
#include "GameObject.h"

void dae::FPSComponent::Update(float const elapsedTime)
{
	m_FrameCount++;
	m_Delay += elapsedTime;

	if (m_Delay >= m_MaxDelay)
	{
		m_CurrentFPS = m_FrameCount/m_Delay;

		m_FrameCount = 0;
		m_Delay = 0;
	}

	if (m_SetTextToFPS)
	{
		try
		{
			auto& textComponent{ GetOwner()->GetComponent<dae::TextComponent>() };

			std::stringstream stream;
			stream << std::fixed << std::setprecision(1) << m_CurrentFPS << " FPS";
			textComponent.SetText(stream.str());
		}
		catch (const std::runtime_error&)
		{

		}
	}

}

dae::FPSComponent::FPSComponent(dae::GameObject* object, bool setText) : Component(object),
	 m_SetTextToFPS(setText)
{
}
