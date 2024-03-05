#ifndef ROTATORCOMPONENT
#define ROTATORCOMPONENT
#include "Component.h"
#include "Transform.h"

namespace dae
{
	class RotatorComponent : public Component
	{
	public:
		void Update(float const elapsedTime) override;

		void SetSpeed(float const newSpeed) { m_Speed = newSpeed; }
		void SetRadius(float const newRadius) { m_Radius = newRadius; }
		void SetCenter(const Transform&  newCenter) { m_Center = newCenter; }

		RotatorComponent(dae::GameObject* object);
		virtual ~RotatorComponent() override = default;
		RotatorComponent(const RotatorComponent& other) = delete;
		RotatorComponent(RotatorComponent&& other) = delete;
		RotatorComponent& operator= (const RotatorComponent& other) = delete;
		RotatorComponent& operator=(RotatorComponent&& other) = delete;
	private:
		float m_Speed{ 3000 };
		float m_Radius{ 15 };
		float m_Angle{};
		Transform m_Center{};
	};
}

#endif 