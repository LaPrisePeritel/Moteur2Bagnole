#pragma once

#include <A4Engine/Export.hpp>
#include <A4Engine/Shape.hpp>

class A4ENGINE_API BoxShape : Shape
{
public:
	BoxShape(float width, float height);
	~BoxShape() = default;

private:
	float m_width;
	float m_height;
};