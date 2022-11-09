#pragma once

#include <A4Engine/Export.hpp>
#include <A4Engine/Shape.hpp>

class A4ENGINE_API SegmentShape : public Shape
{
public:
	SegmentShape(cpVect vector1, cpVect vector2);
	~SegmentShape() = default;

	cpShape* CreateShape(cpBody* body) override;
	float GetMoment(float mass) override;

private:
	cpVect m_vector1;
	cpVect m_vector2;
};