#include <A4Engine/RigidBodyComponent.hpp>

RigidBodyComponent::RigidBodyComponent(float mass, float width, float height)
{
	m_body = cpBodyNew(mass, cpMomentForBox(mass, width, height));
}

RigidBodyComponent::~RigidBodyComponent()
{
	cpBodyFree(m_body);
}

cpBody* RigidBodyComponent::GetBody()
{
	return m_body;
}

cpVect RigidBodyComponent::GetPosition()
{
	return cpBodyGetPosition(m_body);
}

float RigidBodyComponent::GetAngle()
{
	return cpBodyGetAngle(m_body);
}

void RigidBodyComponent::SetPosition(cpVect pos)
{
	cpBodySetPosition(m_body, pos);
}

void RigidBodyComponent::SetAngle(float angle)
{
	cpBodySetAngle(m_body, angle);
}