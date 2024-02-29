#include "Transform.h"
#include "Minigin.h"

void dae::Transform::SetPosition(float const x, float const y, float const z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}

void dae::Transform::SetLoopable(bool const loop)
{
	m_Loop = loop;
}

void dae::Transform::Move(const Transform& addedPosition)
{
	Move(addedPosition.m_position.x, addedPosition.m_position.y, addedPosition.m_position.z);
}

void dae::Transform::Move(float const addedX, float const addedY, float const addedZ)
{
	if (m_Loop)
	{
		m_position.x = static_cast<float>(static_cast<int>(m_position.x + addedX) % dae::Minigin::m_WindowWidth);
		m_position.y = static_cast<float>(static_cast<int>(m_position.y + addedY) % dae::Minigin::m_WindowHeight);
	}
	else
	{
		m_position.x += addedX;
		m_position.y += addedY;
	}
	m_position.z += addedZ;
}

dae::Transform::Transform() : 
	m_position()
{
}

dae::Transform::Transform(float const x, float const y, float const z)
{
	SetPosition(x, y, z);
}

dae::Transform dae::Transform::operator+(const dae::Transform& other) const
{
	return dae::Transform(m_position.x + other.m_position.x, m_position.y + other.m_position.y, m_position.z + other.m_position.z);
}

dae::Transform dae::Transform::operator-() const
{
	return dae::Transform(-m_position.x, -m_position.y, -m_position.z);
}

dae::Transform dae::Transform::operator-(const dae::Transform& other) const
{
	return operator+(-other);
}

