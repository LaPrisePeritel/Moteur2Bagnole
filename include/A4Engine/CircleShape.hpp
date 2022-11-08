#pragma once

#include <A4Engine/Export.hpp>
#include <A4Engine/Shape.hpp>

class A4ENGINE_API CircleShape : Shape
{
public:
	CircleShape(float radius, cpVect offset);
	~CircleShape() = default;

	cpShape* CreateShape(cpBody* body) override;
	float GetMoment(float mass) override;

private:
	float m_radius;
	cpVect m_offset;
};