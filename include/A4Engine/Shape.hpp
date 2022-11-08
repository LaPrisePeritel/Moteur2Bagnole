#pragma once

#include <A4Engine/Export.hpp>
#include <chipmunk/chipmunk.h>

class A4ENGINE_API Shape
{
public:
	Shape() = default;
	~Shape() = default;

	// Create Shape
	cpShape* GetShape()
	{
		return m_shape;
	}

private:
	cpShape* m_shape;
};