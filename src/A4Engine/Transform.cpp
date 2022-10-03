#include <A4Engine/Transform.hpp>
#include <A4Engine/Math.hpp>

Transform::Transform() :
m_position(0.f, 0.f),
m_rotation(0.f),
m_scale(1.f, 1.f)
{
}

const Vector2f& Transform::GetPosition() const
{
	return m_position;
}

float Transform::GetRotation() const
{
	return m_rotation;
}

const Vector2f& Transform::GetScale() const
{
	return m_scale;
}

void Transform::Rotate(float rotation)
{
	m_rotation += rotation;
}

void Transform::Scale(float scale)
{
	m_scale *= scale;
}

void Transform::Scale(const Vector2f& scale)
{
	m_scale *= scale;
}

void Transform::SetPosition(const Vector2f& position)
{
	m_position = position;
}

void Transform::SetRotation(float rotation)
{
	m_rotation = rotation;
}

void Transform::SetScale(const Vector2f& scale)
{
	m_scale = scale;
}

void Transform::Translate(const Vector2f& translation)
{
	m_position += translation;
}

Vector2f Transform::TransformPoint(Vector2f position)
{
	position *= m_scale;

	float radRotation = Deg2Rad * m_rotation;
	float s = std::sin(radRotation);
	float c = std::cos(radRotation);

	Vector2f rotatedVec;
	rotatedVec.x = position.x * c - position.y * s;
	rotatedVec.y = position.x * s + position.y * c;

	rotatedVec += m_position;

	return rotatedVec;
}
