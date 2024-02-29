#ifndef ROTATORCOMPONENT
#define ROTATORCOMPONENT
#include "Component.h"

namespace dae
{
	class RotatorComponent : public Component
	{
	public:

		RotatorComponent(dae::GameObject* object);
		virtual ~RotatorComponent() override = default;
		RotatorComponent(const RotatorComponent& other) = delete;
		RotatorComponent(RotatorComponent&& other) = delete;
		RotatorComponent& operator= (const RotatorComponent& other) = delete;
		RotatorComponent& operator=(RotatorComponent&& other) = delete;
	private:
		float m_Speed{};
	};
}

#endif 