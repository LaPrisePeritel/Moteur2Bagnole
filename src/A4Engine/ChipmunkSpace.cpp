#include <A4Engine/ChipmunkSpace.hpp>
#include <chipmunk/chipmunk.h>
#include <algorithm>

ChipmunkSpace::ChipmunkSpace()
{
	m_handle = cpSpaceNew();
}

ChipmunkSpace::ChipmunkSpace(ChipmunkSpace&& space) noexcept
{
	m_handle = space.m_handle;
	space.m_handle = nullptr;
}

ChipmunkSpace::~ChipmunkSpace()
{
	if (m_handle)
		cpSpaceFree(m_handle);
}

cpSpace* ChipmunkSpace::GetHandle() const
{
	return m_handle;
}

void ChipmunkSpace::SetDamping(float damping)
{
	cpSpaceSetDamping(m_handle, damping);
}

void ChipmunkSpace::SetGravity(const Vector2f& gravity)
{
	cpSpaceSetGravity(m_handle, cpv(gravity.x, gravity.y));
}

void ChipmunkSpace::Step(float deltaTime)
{
	cpSpaceStep(m_handle, deltaTime);
}

ChipmunkSpace& ChipmunkSpace::operator=(ChipmunkSpace&& space) noexcept
{
	// On possède déjà potentiellement une Surface
	// On la donne à Surface (qui va être détruit de toute façon)
	// tout en volant son pointeur : on échange donc les pointeurs
	// => std::swap
	std::swap(m_handle, space.m_handle);
	return *this;
}
