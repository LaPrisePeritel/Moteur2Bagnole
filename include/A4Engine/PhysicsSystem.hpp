#pragma once

#include <A4Engine/Export.hpp>
<<<<<<< HEAD
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
=======
#include <A4Engine/ChipmunkSpace.hpp>
#include <entt/fwd.hpp>

class A4ENGINE_API PhysicsSystem : ChipmunkSpace //< héritage privé, les méthodes ne sont pas accessibles publiquement
{
	public:
		PhysicsSystem(entt::registry& registry);
		PhysicsSystem(const PhysicsSystem&) = delete;
		PhysicsSystem(PhysicsSystem&&) = default;
		~PhysicsSystem();

		ChipmunkSpace& GetSpace();

		// Cette syntaxe permet d'exposer publiquement des méthodes cachées du parent
		using ChipmunkSpace::DebugDraw;
		using ChipmunkSpace::SetDamping;
		using ChipmunkSpace::SetGravity;

		void Update(float deltaTime);

		PhysicsSystem& operator=(const PhysicsSystem&) = delete;
		PhysicsSystem& operator=(PhysicsSystem&&) = delete;

		static PhysicsSystem* Instance();

	private:
		entt::registry& m_registry;
		float m_accumulator;
		float m_timestep;

		static PhysicsSystem* s_instance;
};
>>>>>>> bba2d7d5c19aec8963b1c4354fae048cc291dbd3
