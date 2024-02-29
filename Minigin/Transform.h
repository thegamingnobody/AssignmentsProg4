#ifndef TRANSFORM
#define TRANSFORM
#include <glm/glm.hpp>

namespace dae
{
	class Transform final
	{
	public:
		const glm::vec3& GetPosition() const { return m_position; }
		void SetPosition(float const x, float const y, float const z);

		void SetLoopable(bool const loop);

		void Move(const Transform& addedPosition);
		void Move(float const addedX, float const addedY, float const addedZ);

		Transform();
		Transform(float const x, float const y, float const z);


		Transform operator+(const Transform& other) const;
		Transform operator-() const;
		Transform operator-(const Transform& other) const;
	private:
		bool m_Loop{false};
		glm::vec3 m_position;
	};
}

#endif