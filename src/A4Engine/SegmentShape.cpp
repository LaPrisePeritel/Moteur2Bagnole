#include <A4Engine/SegmentShape.hpp>

SegmentShape::SegmentShape(cpVect vector1, cpVect vector2)
{
	m_vector1 = vector1;
	m_vector2 = vector2;
}

cpShape* SegmentShape::CreateShape(cpBody* body)
{
	return m_shape = cpSegmentShapeNew(body, m_vector1, m_vector2, 0.0f);
}

float SegmentShape::GetMoment(float mass)
{
	return cpMomentForSegment(mass, m_vector1, m_vector2, 0.0f);
}
