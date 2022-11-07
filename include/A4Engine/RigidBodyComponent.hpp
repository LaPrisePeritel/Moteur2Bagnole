#pragma once

#include <A4Engine/Export.hpp>
#include <chipmunk/chipmunk.h>
#include <A4Engine/Transform.hpp>

class A4ENGINE_API RigidBodyComponent 
{
public:
	RigidBodyComponent(float mass);
	RigidBodyComponent(RigidBodyComponent&&) noexcept;
	~RigidBodyComponent() = default;

	static void AttachRigidBody(Transform* parent);
	static void DetachRigidBody();

private:
	cpBody* m_body;
	cpShape* shape;
};
