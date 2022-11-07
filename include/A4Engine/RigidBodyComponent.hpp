#pragma once

#include <A4Engine/Export.hpp>
#include <chipmunk/chipmunk.h>

class A4ENGINE_API RigidBodyComponent {

public:

	RigidBodyComponent(float mass, float width, float height);
	RigidBodyComponent(const RigidBodyComponent&) = default;
	RigidBodyComponent(RigidBodyComponent&&) = default;
	~RigidBodyComponent();

	RigidBodyComponent& operator=(const RigidBodyComponent&) = default;
	RigidBodyComponent& operator=(RigidBodyComponent&&) = default;

	cpBody* GetBody();

	cpVect GetPosition();
	float GetAngle();
	void SetPosition(cpVect pos);
	void SetAngle(float angle);

private:
	cpBody* m_body;

};
