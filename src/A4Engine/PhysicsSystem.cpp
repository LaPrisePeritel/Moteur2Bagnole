#include <A4Engine/PhysicsSystem.hpp>
#include <A4Engine/Transform.hpp>


PhysicsSystem::PhysicsSystem(entt::registry& registry): 
m_registry(registry)
{
	m_space = cpSpaceNew();

	SetGravity(981);
	SetDamping(.5f);
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

cpSpace* PhysicsSystem::GetSpace()
{
	return m_space;
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

void PhysicsSystem::Update(float deltaTime)
{
	auto RigidBodyView = m_registry.view<RigidBodyComponent, Transform>();
	for (entt::entity entity : RigidBodyView)
	{
		RigidBodyComponent& entityRigidBody = RigidBodyView.get<RigidBodyComponent>(entity);
		Transform& entityTransform = RigidBodyView.get<Transform>(entity);

		cpVect pos = entityRigidBody.GetPosition();
		float rot = entityRigidBody.GetAngle() * Rad2Deg;

		entityTransform.SetPosition(Vector2f(pos.x, pos.y));
		entityTransform.SetRotation(rot);
	}
}