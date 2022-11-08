#include <A4Engine/PhysicsSystem.hpp>


PhysicsSystem::PhysicsSystem(float gravity, float damping, float timeStep) :
	m_timeStep(timeStep)
{
	m_space = cpSpaceNew();
	SetGravity(gravity);
	SetDamping(damping);
}

PhysicsSystem::~PhysicsSystem()
{
	for (int i = bodies.size() - 1; i >= 0; i--) {
		RemoveBody(bodies[i]);
	}
	cpSpaceFree(m_space);
}

float PhysicsSystem::GetGravity()
{
	return cpSpaceGetGravity(m_space).y;
}

float PhysicsSystem::GetDamping()
{
	return cpSpaceGetDamping(m_space);
}

void PhysicsSystem::SetGravity(float value)
{
	cpSpaceSetGravity(m_space, cpv(0, value));
}

void PhysicsSystem::SetDamping(float value)
{
	cpSpaceSetDamping(m_space, value);
}

void PhysicsSystem::AddBody(RigidBodyComponent& body)
{
	cpSpaceAddBody(m_space, body.GetBody());
	bodies.push_back(body);
}

void PhysicsSystem::RemoveBody(RigidBodyComponent& body)
{
	cpSpaceRemoveBody(m_space, body.GetBody());
	body.~RigidBodyComponent();
}

void PhysicsSystem::Step(float deltaTime)
{
	m_physicsAccumulator += deltaTime;
	while (m_physicsAccumulator >= m_timeStep) {
		cpSpaceStep(m_space, m_timeStep);
		m_physicsAccumulator -= m_timeStep;
	}
}