#include <A4Engine/Vector3.hpp>
#include <A4Engine/Math.hpp>
#include <cmath>
<<<<<<< HEAD
// le #pragma once n'est pas nécessaire ici, un seul fichier va nous inclure directement et il est déjà protégé

template<typename T>
Vector3<T>::Vector3(T V) :
	x(V),
	y(V),
	z(V)
=======

template<typename T>
Vector3<T>::Vector3(T V) :
x(V),
y(V),
z(V)
>>>>>>> bba2d7d5c19aec8963b1c4354fae048cc291dbd3
{
}

template<typename T>
Vector3<T>::Vector3(T X, T Y, T Z) :
<<<<<<< HEAD
	x(X),
	y(Y),
	z(Z)
=======
x(X),
y(Y),
z(Z)
>>>>>>> bba2d7d5c19aec8963b1c4354fae048cc291dbd3
{
}

template<typename T>
Vector3<T> Vector3<T>::operator+(const Vector3& vec) const
{
	return Vector3{ x + vec.x, y + vec.y, z + vec.z };
}

template<typename T>
Vector3<T> Vector3<T>::operator-(const Vector3& vec) const
{
	return Vector3{ x - vec.x, y - vec.y, z - vec.z };
}

template<typename T>
Vector3<T> Vector3<T>::operator*(const Vector3& vec) const
{
	return Vector3{ x * vec.x, y * vec.y, z * vec.z };
}

template<typename T>
Vector3<T> Vector3<T>::operator*(T value) const
{
	return Vector3{ x * value, y * value, z * value };
}

template<typename T>
Vector3<T> Vector3<T>::operator/(const Vector3& vec) const
{
	return Vector3{ x / vec.x, y / vec.y, z / vec.z };
}

template<typename T>
Vector3<T> Vector3<T>::operator/(T value) const
{
	return Vector3{ x / value, y / value, z / value };
}

template<typename T>
Vector3<T>& Vector3<T>::operator+=(const Vector3& vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;

	return *this;
}

template<typename T>
Vector3<T>& Vector3<T>::operator-=(const Vector3& vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;

	return *this;
}

template<typename T>
Vector3<T>& Vector3<T>::operator*=(const Vector3& vec)
{
	x *= vec.x;
	y *= vec.y;
	z *= vec.z;

	return *this;
}

template<typename T>
Vector3<T>& Vector3<T>::operator*=(T value)
{
	x *= value;
	y *= value;
	z *= value;

	return *this;
}

template<typename T>
Vector3<T>& Vector3<T>::operator/=(const Vector3& vec)
{
	x /= vec.x;
	y /= vec.y;
	z /= vec.z;

	return *this;
}

template<typename T>
Vector3<T>& Vector3<T>::operator/=(T value)
{
	x /= value;
	y /= value;
	z /= value;

	return *this;
}

template<typename T>
Vector3<T> operator*(T value, const Vector3<T>& vec)
{
	return Vector3{ vec.x * value, vec.y * value, vec.z * value };
}

template<typename T>
Vector3<T> operator/(T value, const Vector3<T>& vec)
{
	return Vector3{ vec.x / value, vec.y / value, vec.z / value };
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector3<T>& vec)
{
<<<<<<< HEAD
	return os << "Vector3(" << vec.x << ", " << vec.y  << ", " << vec.z << ")";
=======
	return os << "Vector3(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
>>>>>>> bba2d7d5c19aec8963b1c4354fae048cc291dbd3
}
