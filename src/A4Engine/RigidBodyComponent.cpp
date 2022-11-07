#include <A4Engine/RigidBodyComponent.hpp>

RigidBodyComponent::RigidBodyComponent(float mass)
{
	cpBodySetMass(m_body, mass);
}

RigidBodyComponent::RigidBodyComponent(RigidBodyComponent&&) noexcept
{
}
