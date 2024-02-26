#include "FPSComponent.h"
#include "TextComponent.h"
#include "GameObject.h"

void dae::FPSComponent::Update(float const)
{
	m_FrameCount++;

	auto currentTime{ std::chrono::high_resolution_clock::now() };

	auto timeSinceFpsTimer{ std::chrono::duration_cast<std::chrono::seconds>(currentTime - m_FpsTimer) };
	if (timeSinceFpsTimer.count() >= 1)
	{
		m_CurrentFPS = static_cast<float>(m_FrameCount) / timeSinceFpsTimer.count();

		m_FrameCount = 0;
		m_FpsTimer = std::chrono::high_resolution_clock::now();
	}

	if (m_SetTextToFPS)
	{
		try
		{
			auto& textComponent{ m_pGameObject.get()->GetComponent<dae::TextComponent>() };
			textComponent.SetText(std::to_string(m_CurrentFPS));
		}
		catch (const std::runtime_error&)
		{

		}
	}

}

void dae::FPSComponent::Render() const
{
}

std::shared_ptr<dae::Texture2D> dae::FPSComponent::GetTexture()
{
	return std::shared_ptr<dae::Texture2D>();
}

dae::FPSComponent::FPSComponent(std::shared_ptr<dae::GameObject> object, bool setText) : Component(object),
	 m_SetTextToFPS(setText)
{
	m_FpsTimer = std::chrono::high_resolution_clock::now();
}
