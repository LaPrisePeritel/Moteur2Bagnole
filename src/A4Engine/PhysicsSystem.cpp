#include <A4Engine/PhysicsSystem.hpp>
<<<<<<< HEAD
#include <A4Engine/Transform.hpp>


PhysicsSystem::PhysicsSystem(entt::registry& registry): 
m_registry(registry)
{
	m_space = cpSpaceNew();

	SetGravity(981);
	SetDamping(.5f);
=======
#include <A4Engine/RigidBodyComponent.hpp>
#include <A4Engine/Transform.hpp>
#include <entt/entt.hpp>

PhysicsSystem::PhysicsSystem(entt::registry& registry) :
m_registry(registry),
m_accumulator(0.f),
m_timestep(1.f / 50.f)
{
	// Par mesure de simplicité, on utilise un Singleton ici
	// néanmoins, en pratique les singletons sont un peu le "goto de l'architecture".
	// Il serait mieux de permettre d'avoir plusieurs Space
	if (s_instance != nullptr)
		throw std::runtime_error("only one PhysicsSystem can be created");

	s_instance = this;
>>>>>>> bba2d7d5c19aec8963b1c4354fae048cc291dbd3
}

PhysicsSystem::~PhysicsSystem()
{
<<<<<<< HEAD
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
=======
	// Le PhysicsSystem est détruit avant le registry (qui lui-même détruit les composants RigidBodyComponent, ceux-ci détruisant les cpBody/cpShape)
	// cela pose problème, pour y remédier on va forcer la destruction des composants en les enlevant
	m_registry.clear<RigidBodyComponent>();

	s_instance = nullptr;
}

ChipmunkSpace& PhysicsSystem::GetSpace()
{
	// L'héritage privé interdit à tout autre classe que nous de récupérer une référence sur le parent à partir de nous
	// mais nous pouvons faire une fonction pour l'autoriser
	return *this;
>>>>>>> bba2d7d5c19aec8963b1c4354fae048cc291dbd3
}

void PhysicsSystem::Update(float deltaTime)
{
<<<<<<< HEAD
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
=======
	m_accumulator += deltaTime;
	while (m_accumulator >= m_timestep)
	{
		Step(m_timestep);
		m_accumulator -= m_timestep;
	}

	auto view = m_registry.view<Transform, RigidBodyComponent>();
	for (entt::entity entity : view)
	{
		Transform& entityTransform = view.get<Transform>(entity);
		RigidBodyComponent& entityBody = view.get<RigidBodyComponent>(entity);

		entityTransform.SetPosition(entityBody.GetPosition());
		entityTransform.SetRotation(entityBody.GetRotation());
	}
}

PhysicsSystem* PhysicsSystem::Instance()
{
	return s_instance;
}

PhysicsSystem* PhysicsSystem::s_instance = nullptr;
>>>>>>> bba2d7d5c19aec8963b1c4354fae048cc291dbd3
