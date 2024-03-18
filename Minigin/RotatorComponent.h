#ifndef ROTATORCOMPONENT
#define ROTATORCOMPONENT
#include "Component.h"
#include "Transform.h"
#include <optional>

namespace dae
{
	class RotatorComponent : public Component
	{
	public:
		void Update(float const elapsedTime) override;

		void SetSpeed(float const newSpeed) { m_Speed = newSpeed; }
		void SetRadius(float const newRadius) { m_Radius = newRadius; }

		RotatorComponent(dae::GameObject* object, float const speed = 3000.0f, float const radius = 15.0f);
		virtual ~RotatorComponent() override = default;
		RotatorComponent(const RotatorComponent& other) = delete;
		RotatorComponent(RotatorComponent&& other) = delete;
		RotatorComponent& operator= (const RotatorComponent& other) = delete;
		RotatorComponent& operator=(RotatorComponent&& other) = delete;
	private:
		float m_Speed{};
		float m_Radius{};
		float m_Angle{};
		std::optional<Transform*> m_OwnerTransformComponent;
	};
}

#endif 