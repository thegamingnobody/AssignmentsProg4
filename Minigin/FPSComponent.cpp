#include "FPSComponent.h"

void dae::FPSComponent::Update(float const elapsedTime)
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
}

void dae::FPSComponent::Render() const
{
}

std::shared_ptr<dae::Texture2D> dae::FPSComponent::GetTexture()
{
	return std::shared_ptr<dae::Texture2D>();
}

dae::FPSComponent::FPSComponent()
{
	m_FpsTimer = std::chrono::high_resolution_clock::now();
}
