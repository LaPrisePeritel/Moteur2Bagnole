#include <A4Engine/CircleShape.hpp>

CircleShape::CircleShape(float radius, cpVect offset)
{
	m_radius = radius;
	m_offset = offset;
}

cpShape* CircleShape::CreateShape(cpBody* body)
{
	return m_shape = cpCircleShapeNew(body, m_radius, m_offset);
}

float CircleShape::GetMoment(float mass)
{
	return cpMomentForCircle(mass, m_radius * 2.f, m_radius * 2.f, m_offset);
}
