#pragma once

#include <A4Engine/Export.hpp>
#include <A4Engine/Vector2.hpp>

struct cpSpace;

class A4ENGINE_API ChipmunkSpace
{
	public:
		ChipmunkSpace();
		ChipmunkSpace(const ChipmunkSpace&) = delete;
		ChipmunkSpace(ChipmunkSpace&& space) noexcept;
		~ChipmunkSpace();

		cpSpace* GetHandle() const;

		void SetDamping(float damping);
		void SetGravity(const Vector2f& gravity);

		void Step(float deltaTime);

		ChipmunkSpace& operator=(const ChipmunkSpace&) = delete;
		ChipmunkSpace& operator=(ChipmunkSpace&& space) noexcept;

	private:
		cpSpace* m_handle;
};