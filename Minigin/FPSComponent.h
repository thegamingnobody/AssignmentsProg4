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

		int GetFrameCount() const { return m_FrameCount; }
		float GetFPS() const { return m_CurrentFPS; }

		FPSComponent(dae::GameObject* object);
		virtual ~FPSComponent() override = default;
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator= (const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;
	private:
		int m_FrameCount{};
		float m_CurrentFPS{};
		float m_Delay{};
		float const m_MaxDelay{ 0.10f };
	};
}
#endif