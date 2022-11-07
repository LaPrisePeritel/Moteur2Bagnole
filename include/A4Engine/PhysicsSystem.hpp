#pragma once

#include <A4Engine/Export.hpp>
#include <chipmunk/chipmunk.h>
#include <A4Engine/RigidBodyComponent.hpp>
#include <vector>

class A4ENGINE_API PhysicsSystem {
public:

	PhysicsSystem(float gravity, float damping, float timeStep);
	PhysicsSystem(const PhysicsSystem&) = delete;
	PhysicsSystem(PhysicsSystem&&) = delete;
	~PhysicsSystem();

	PhysicsSystem& operator=(const PhysicsSystem&) = delete;
	PhysicsSystem& operator=(PhysicsSystem&&) = delete;

	float GetGravity();
	float GetDamping();
	void SetGravity(float value);
	void SetDamping(float value);

	void AddBody(RigidBodyComponent& body);
	void RemoveBody(RigidBodyComponent& body);

	void Step(float deltaTime);

private:
	cpSpace* m_space;
	std::vector<RigidBodyComponent> bodies;

	float m_timeStep;
	float m_physicsAccumulator;

};
