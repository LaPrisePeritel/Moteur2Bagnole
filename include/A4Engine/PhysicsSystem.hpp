#pragma once

#include <A4Engine/Export.hpp>
#include <chipmunk/chipmunk.h>
#include <entt/entt.hpp>
#include <A4Engine/RigidBodyComponent.hpp>
#include <vector>

class A4ENGINE_API PhysicsSystem {
public:

	PhysicsSystem(entt::registry& registry);
	PhysicsSystem(const PhysicsSystem&) = delete;
	PhysicsSystem(PhysicsSystem&&) = delete;
	~PhysicsSystem();

	PhysicsSystem& operator=(const PhysicsSystem&) = delete;
	PhysicsSystem& operator=(PhysicsSystem&&) = delete;

	float GetGravity();
	float GetDamping();
	cpSpace* GetSpace();
	void SetGravity(float value);
	void SetDamping(float value);

	void AddBody(RigidBodyComponent& body);
	void RemoveBody(RigidBodyComponent& body);

	void Step(float deltaTime);
	void Update(float deltaTime);

private:
	entt::registry& m_registry;

	cpSpace* m_space;
	std::vector<RigidBodyComponent> bodies;

	float m_timeStep = 1.f / 50;
	float m_physicsAccumulator;

};
