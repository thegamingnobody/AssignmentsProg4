#ifndef TRANSFORM
#define TRANSFORM

#include <glm/glm.hpp>
#include "Component.h"
#include <any>
#include "Observer.h"


namespace dae
{
	class Transform : public Component, public Observer
	{
	public:
		void Update(float const elapsedTime) override;

		void Reset();
		const glm::vec3& GetPosition();
		void SetPosition(float const x, float const y);

		void SetShouldUpdate(bool const shouldUpdate) { m_ShouldUpdate = shouldUpdate; }
		bool GetShouldUpdate() const { return m_ShouldUpdate; }

		void Move(float const addedX, float const addedY);
		void ResetDirection(bool const resetX, bool const resetY);

		Transform(dae::GameObject* object);
		Transform(dae::GameObject* object, float const x, float const y);

		void Notify(const Event& event) override;

	private:
		bool m_ShouldUpdate{ true };

		glm::vec3 m_LocalPosition;
		glm::vec3 m_WorldPosition;

		glm::vec3 m_DirectionThisFrame;

		glm::vec3 m_ParentWorldPos;

		glm::vec3 m_PredictedWorldPos;
	};
}

#endif