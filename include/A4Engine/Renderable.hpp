#pragma once

#include <A4Engine/Export.hpp>
#include <A4Engine/Matrix3.hpp>

class SDLppRenderer;
class SDLppTexture;
class Transform;
class Matrix3;

class A4ENGINE_API Renderable // interface
{
	public:
		// Il est important pour une classe virtuelle de base d'avoir un destructeur virtuel
		virtual ~Renderable() = default;

<<<<<<< HEAD
		virtual void Draw(SDLppRenderer& renderer, const Matrix3& matrix) = 0;
=======
		virtual void Draw(SDLppRenderer& renderer, const Matrix3f& matrix) = 0;
>>>>>>> bba2d7d5c19aec8963b1c4354fae048cc291dbd3
};
