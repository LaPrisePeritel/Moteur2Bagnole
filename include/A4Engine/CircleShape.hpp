#pragma once

#include <A4Engine/Export.hpp>
#include <A4Engine/Shape.hpp>

class A4ENGINE_API CircleShape : Shape
{
public:
	CircleShape(float radius);
	~CircleShape() = default;

private:
	float m_radius;
};