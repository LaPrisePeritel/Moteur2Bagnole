#pragma once

#include <A4Engine/Export.hpp>
#include <A4Engine/Vector2.hpp>

class A4ENGINE_API Matrix3
{
public:
	Matrix3() = default;
	Matrix3(const Matrix3&);
	~Matrix3() = default;

	Matrix3& operator*(const Vector2f& value) const;
	Matrix3& operator*(float value);
	Matrix3& operator*=(const Vector2f& value) const;
	Matrix3& operator*=(float value);

private:
	float m_matrix[3][3];
};
