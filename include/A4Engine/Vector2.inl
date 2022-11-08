#include <A4Engine/Vector2.hpp>
#include <A4Engine/Math.hpp>
#include <cmath>
#include <A4Engine/Matrix3.hpp>
#include <fmt/core.h>
// le #pragma once n'est pas nécessaire ici, un seul fichier va nous inclure directement et il est déjà protégé

template<typename T>
Vector2<T>::Vector2(T V) :
x(V),
y(V)
{
}

template<typename T>
Vector2<T>::Vector2(T X, T Y) :
x(X),
y(Y)
{
}

template<typename T>
Vector2<T> Vector2<T>::operator+(const Vector2& vec) const
{
	return Vector2{ x + vec.x, y + vec.y };
}

template<typename T>
Vector2<T> Vector2<T>::operator-(const Vector2& vec) const
{
	return Vector2{ x - vec.x, y - vec.y };
}

template<typename T>
Vector2<T> Vector2<T>::operator*(const Vector2& vec) const
{
	return Vector2{ x * vec.x, y * vec.y };
}

template<typename T>
Vector2<T> Vector2<T>::operator*(T value) const
{
	return Vector2{ x * value, y * value };
}

template<typename T>
Vector2<T> Vector2<T>::operator/(const Vector2& vec) const
{
	return Vector2{ x / vec.x, y / vec.y };
}

template<typename T>
Vector2<T> Vector2<T>::operator/(T value) const
{
	return Vector2{ x / value, y / value };
}

template<typename T>
Vector2<T>& Vector2<T>::operator+=(const Vector2& vec)
{
	x += vec.x;
	y += vec.y;

	return *this;
}

template<typename T>
Vector2<T>& Vector2<T>::operator-=(const Vector2& vec)
{
	x -= vec.x;
	y -= vec.y;

	return *this;
}

template<typename T>
Vector2<T>& Vector2<T>::operator*=(const Vector2& vec)
{
	x *= vec.x;
	y *= vec.y;

	return *this;
}

template<typename T>
Vector2<T>& Vector2<T>::operator*=(T value)
{
	x *= value;
	y *= value;

	return *this;
}

template<typename T>
Vector2<T>& Vector2<T>::operator/=(const Vector2& vec)
{
	x /= vec.x;
	y /= vec.y;

	return *this;
}

template<typename T>
Vector2<T>& Vector2<T>::operator/=(T value)
{
	x /= value;
	y /= value;

	return *this;
}

template<typename T>
Vector2<T> Vector2<T>::operator*(const Matrix3& matrix) const
{
	float vIn[3] = { x, y, 1 };
	float vOut[3]{};

	for (auto i = 0; i < 3; i++)
		for (auto j = 0; j < 3; j++)
			vOut[i] += matrix(i, j) * vIn[j];

	return Vector2(vOut[0], vOut[1]);
}

template<typename T>
Vector2<T> Vector2<T>::Rotate(const Vector2& vec, float degrees)
{
	float radRotation = Deg2Rad * degrees;
	float s = std::sin(radRotation);
	float c = std::cos(radRotation);

	Vector2 rotatedVec;
	rotatedVec.x = vec.x * c - vec.y * s;
	rotatedVec.y = vec.x * s + vec.y * c;

	return rotatedVec;
}

template<typename T>
Vector2<T> operator*(T value, const Vector2<T>& vec)
{
	return Vector2{ vec.x * value, vec.y * value };
}

template<typename T>
Vector2<T> operator/(T value, const Vector2<T>& vec)
{
	return Vector2{ vec.x / value, vec.y / value };
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector2<T>& vec)
{
	return os << "Vector2(" << vec.x << ", " << vec.y << ")";
}
