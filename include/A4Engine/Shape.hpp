#pragma once

#include <A4Engine/Export.hpp>
#include <chipmunk/chipmunk.h>

class A4ENGINE_API Shape
{
public:
	Shape() = default;
	~Shape() = default;

	virtual cpShape* CreateShape(cpBody* body) = 0;
	inline cpShape* GetShape() { return m_shape; }

	virtual float GetMoment(float mass) = 0;

protected:
	cpShape* m_shape;
};