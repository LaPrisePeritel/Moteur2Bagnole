#pragma once

#include <A4Engine/Export.hpp>
#include <A4Engine/Vector2.hpp>

class A4ENGINE_API Transform
{
	public:
		Transform();
		Transform(const Transform&) = default;
		Transform(Transform&&) = default;
		~Transform() = default;

		const Vector2f& GetPosition() const;
		float GetRotation() const;
		const Vector2f& GetScale() const;

		void Rotate(float rotation);
		void Scale(float scale);
		void Scale(const Vector2f& scale);

		void SetPosition(const Vector2f& position);
		void SetRotation(float rotation);
		void SetScale(const Vector2f& scale);

		void Translate(const Vector2f& translation);

		Vector2f TransformPoint(Vector2f position);

		Transform& operator=(const Transform&) = default;
		Transform& operator=(Transform&&) = default;

	private:
		Vector2f m_position;
		float m_rotation;
		Vector2f m_scale;
};