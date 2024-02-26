#ifndef FPSCOMPONENT
#define FPSCOMPONENT
#include "Component.h"
#include "Transform.h"
#include <chrono>

namespace dae 
{
	class FPSComponent : public Component
	{
	public:
		void Update(float const elapsedTime) override;
		void Render() const override;

		void SetPosition(float x, float y) { m_transform.SetPosition(x, y, 0.0f); }
		void SetTextToFPS(bool setText) { m_SetTextToFPS = setText; }

		std::shared_ptr<dae::Texture2D> GetTexture() override;

		int GetFrameCount() const { return m_FrameCount; }
		float GetFPS() const { return m_CurrentFPS; }

		FPSComponent(std::weak_ptr<dae::GameObject> object, bool setText = false);
		virtual ~FPSComponent() override = default;
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator= (const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;
	private:
		Transform m_transform{};
		int m_FrameCount{};
		float m_CurrentFPS{};
		float m_Delay{};
		float const m_MaxDelay{ 0.10f };
		bool m_SetTextToFPS{ false };
	};
}
#endif