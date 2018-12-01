/**
 * Project AltMath
 * @author GP2021
 * @version 1.0.0
 */

#pragma once
#ifndef _VECTOR3_INL
#define _VECTOR3_INL

#include "Vector2.h"
#include "AltMath/Tools/Utils.h"

namespace AltMath
{
	template <typename T>
	const Vector3<T> Vector3<T>::Zero = Vector3<float>(0, 0, 0);
	template <typename T>
	const Vector3<T> Vector3<T>::XAxis = Vector3<T>(1, 0, 0);
	template <typename T>
	const Vector3<T> Vector3<T>::YAxis = Vector3<T>(0, 1, 0);
	template <typename T>
	const Vector3<T> Vector3<T>::ZAxis = Vector3<T>(0, 0, 1);

#pragma region Constructors & Assignment

	template <typename T>
	constexpr Vector3<T>::Vector3()
		: x(0), y(0), z(0) {}

	template <typename T>
	constexpr Vector3<T>::Vector3(T p_x, T p_y, T p_z)
		: x(p_x), y(p_y), z(p_z) {}

	template <typename T>
	constexpr Vector3<T>::Vector3(const Vector2<T>& p_other)
		: x(p_other.x), y(p_other.y), z(0) {}

	template <typename T>
	constexpr Vector3<T>::Vector3(Vector2<T>&& p_other)
		: x(p_other.x), y(p_other.y), z(0) {}

	template <typename T>
	constexpr Vector3<T>::Vector3(const Vector3<T>& p_other)
	{
		*this = p_other;
	}

	template <typename T>
	constexpr Vector3<T>::Vector3(Vector3<T>&& p_other)
	{
		*this = p_other;
	}

	template <typename T>
	constexpr Vector3<T>& Vector3<T>::operator=(const Vector3<T>& p_other)
	{
		x = p_other.x;
		y = p_other.y;
		z = p_other.z;

		return *this;
	}

	template <typename T>
	constexpr Vector3<T>& Vector3<T>::operator=(Vector3<T>&& p_other)
	{
		x = p_other.x;
		y = p_other.y;
		z = p_other.z;

		return *this;
	}

#pragma endregion
#pragma region Tests & Comparisons

	template <typename T>
	constexpr bool Vector3<T>::IsParallelTo(const Vector3<T>& p_other) const
	{
		return (Vector3<T>::Normalize(*this) == Vector3<T>::Normalize(p_other) ||
			Vector3<T>::Normalize(*this) == (Vector3<T>::Normalize(p_other) * -1));
	}

	template <typename T>
	constexpr bool Vector3<T>::AreParallel(const Vector3<T>& p_left, const Vector3<T>& p_right)
	{
		return p_left.IsParallelTo(p_right);
	}

	template <typename T>
	constexpr bool Vector3<T>::IsPerpendicularTo(const Vector3<T>& p_other) const
	{
		return DotProduct(p_other) == 0;
	}

	template <typename T>
	constexpr bool Vector3<T>::ArePerpendicular(const Vector3<T>& p_left, const Vector3<T>& p_right)
	{
		return p_left.IsPerpendicularTo(p_right);
	}

	template <typename T>
	constexpr bool Vector3<T>::IsEqualTo(const Vector3<T>& p_other) const
	{
		return (x == p_other.x && y == p_other.y && z == p_other.z);
	}

	template <typename T>
	constexpr bool Vector3<T>::AreEqual(const Vector3<T>& p_left, const Vector3<T>& p_right)
	{
		return p_left.IsEqualTo(p_right);
	}

	template <typename T>
	constexpr bool Vector3<T>::operator==(const Vector3<T>& p_other) const
	{
		return IsEqualTo(p_other);
	}

#pragma endregion
#pragma region Arithmetic Operations

#pragma region Add

	template <typename T>
	Vector3<T>& Vector3<T>::Add(T p_scalar)
	{
		x += p_scalar;
		y += p_scalar;
		z += p_scalar;

		return *this;
	}

	template <typename T>
	constexpr Vector3<T> Vector3<T>::Add(const Vector3<T>& p_left, T p_scalar)
	{
		return Vector3<T>(p_left).Add(p_scalar);
	}

	template <typename T>
	Vector3<T>& Vector3<T>::Add(const Vector3<T>& p_other)
	{
		x += p_other.x;
		y += p_other.y;
		z += p_other.z;

		return *this;
	}

	template <typename T>
	constexpr Vector3<T> Vector3<T>::Add(const Vector3<T>& p_left, const Vector3<T>& p_right)
	{
		return Vector3<T>(p_left).Add(p_right);
	}

	template <typename T>
	constexpr Vector3<T> Vector3<T>::operator+(T p_scalar) const
	{
		return Vector3<T>(*this).Add(p_scalar);
	}

	template <typename T>
	Vector3<T>& Vector3<T>::operator+=(T p_scalar)
	{
		return Add(p_scalar);
	}

	template <typename T>
	constexpr Vector3<T> Vector3<T>::operator+(const Vector3<T>& p_other) const
	{
		return Vector3<T>(*this).Add(p_other);
	}

	template <typename T>
	Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& p_other)
	{
		return Add(p_other);
	}

#pragma endregion
#pragma region Subtract

	template <typename T>
	Vector3<T>& Vector3<T>::Subtract(T p_scalar)
	{
		x -= p_scalar;
		y -= p_scalar;
		z -= p_scalar;

		return *this;
	}

	template <typename T>
	constexpr Vector3<T> Vector3<T>::Subtract(const Vector3<T>& p_left, T p_scalar)
	{
		return Vector3<T>(p_left).Subtract(p_scalar);
	}

	template <typename T>
	Vector3<T>& Vector3<T>::Subtract(const Vector3<T>& p_other)
	{
		x -= p_other.x;
		y -= p_other.y;
		z -= p_other.z;

		return *this;
	}

	template <typename T>
	constexpr Vector3<T> Vector3<T>::Subtract(const Vector3<T>& p_left, const Vector3<T>& p_right)
	{
		return Vector3<T>(p_left).Subtract(p_right);
	}

	template <typename T>
	constexpr Vector3<T> Vector3<T>::operator-(T p_scalar) const
	{
		return Vector3<T>(*this).Subtract(p_scalar);
	}

	template <typename T>
	Vector3<T>& Vector3<T>::operator-=(T p_scalar)
	{
		return Subtract(p_scalar);
	}

	template <typename T>
	constexpr Vector3<T> Vector3<T>::operator-(const Vector3<T>& p_other) const
	{
		return Vector3<T>(*this).Subtract(p_other);
	}

	template <typename T>
	Vector3<T>& Vector3<T>::operator-=(const Vector3<T>& p_other)
	{
		return Subtract(p_other);
	}

#pragma endregion
#pragma region Multiply

	template <typename T>
	Vector3<T>& Vector3<T>::Multiply(T p_scalar)
	{
		x *= p_scalar;
		y *= p_scalar;
		z *= p_scalar;

		return *this;
	}

	template <typename T>
	constexpr Vector3<T> Vector3<T>::Multiply(const Vector3<T>& p_left, T p_scalar)
	{
		return Vector3<T>(p_left).Multiply(p_scalar);
	}

	template <typename T>
	constexpr Vector3<T> Vector3<T>::operator*(T p_scalar) const
	{
		return Vector3<T>(*this).Multiply(p_scalar);
	}

	template <typename T>
	Vector3<T>& Vector3<T>::operator*=(T p_scalar)
	{
		return Multiply(p_scalar);
	}

#pragma endregion
#pragma region Divide

	template <typename T>
	Vector3<T>& Vector3<T>::Divide(T p_scalar)
	{
		if (abs(0 - p_scalar) > static_cast<T>(0.0001f))
		{
			x /= p_scalar;
			y /= p_scalar;
			z /= p_scalar;
		}

		return *this;
	}

	template <typename T>
	constexpr Vector3<T> Vector3<T>::Divide(const Vector3<T>& p_left, T p_scalar)
	{
		return Vector3<T>(p_left).Divide(p_scalar);
	}

	template <typename T>
	constexpr Vector3<T> Vector3<T>::operator/(T p_scalar) const
	{
		return Vector3<T>(*this).Divide(p_scalar);
	}

	template <typename T>
	Vector3<T>& Vector3<T>::operator/=(T p_scalar)
	{
		return Divide(p_scalar);
	}

#pragma endregion

#pragma endregion
#pragma region Vector Operations

	template <typename T>
	constexpr T Vector3<T>::Length() const
	{
		return (static_cast<T>(Tools::Utils::SquareRootF(x * x + y * y + z * z)));
	}

	template <typename T>
	constexpr T Vector3<T>::Length(const Vector3<T>& p_vector)
	{
		return p_vector.Length();
	}

	template <typename T>
	constexpr T Vector3<T>::LengthSquare() const
	{
		return (static_cast<T>(x * x + y * y + z * z));
	}

	template <typename T>
	constexpr T Vector3<T>::LengthSquare(const Vector3<T>& p_vector)
	{
		return p_vector.LengthSquare();
	}

	template <typename T>
	constexpr T Vector3<T>::DotProduct(const Vector3<T>& p_other) const
	{
		return x * p_other.x + y * p_other.y + z * p_other.z;
	}

	template <typename T>
	constexpr T Vector3<T>::DotProduct(const Vector3<T>& p_left, const Vector3<T>& p_right)
	{
		return p_left.DotProduct(p_right);
	}

	template <typename T>
	constexpr Vector3<T> Vector3<T>::CrossProduct(const Vector3<T>& p_other) const
	{
		return Vector3((y * p_other.z) - (p_other.y * z),
		               (z * p_other.x) - (p_other.z * x),
		               (x * p_other.y) - (p_other.x * y));
	}

	template <typename T>
	constexpr Vector3<T> Vector3<T>::CrossProduct(const Vector3<T>& p_left, const Vector3<T>& p_right)
	{
		return Vector3<T>((p_left.y * p_right.z) - (p_right.y * p_left.z),
		                  (p_left.z * p_right.x) - (p_right.z * p_left.x),
		                  (p_left.x * p_right.y) - (p_right.x * p_left.y));
	}

	template <typename T>
	constexpr T Vector3<T>::TripleProduct(const Vector3<T>& p_left, const Vector3<T>& p_middle,
	                                      const Vector3<T>& p_right)
	{
		const Vector3<T> resultCross = p_middle.CrossProduct(p_right);
		return p_left.DotProduct(resultCross);
	}

	template <typename T>
	constexpr T Vector3<T>::AngleBetween(const Vector3<T>& p_other) const
	{
		float dotProduct = DotProduct(p_other);
		T lengthProduct = Length() * p_other.Length();

		if (lengthProduct > 0)
		{
			T fractionResult = dotProduct / lengthProduct;

			if (fractionResult > -1 && fractionResult < 1)
				return (static_cast<T>(Tools::Utils::Arccos(fractionResult)));
		}

		return 0;
	}

	template <typename T>
	constexpr T Vector3<T>::AngleBetween(const Vector3<T>& p_left, const Vector3<T>& p_right)
	{
		return p_left.AngleBetween(p_right);
	}

	template <typename T>
	Vector3<T>& Vector3<T>::Normalize()
	{
		float length = Length();
		if (length > 0)
		{
			x /= length;
			y /= length;
			z /= length;
		}

		return *this;
	}

	template <typename T>
	constexpr Vector3<T> Vector3<T>::Normalize(const Vector3<T>& p_vector)
	{
		return Vector3<T>(p_vector).Normalize();
	}

	template <typename T>
	constexpr Vector3<T> Vector3<T>::Lerp(const Vector3<T>& p_start, const Vector3<T>& p_end,
	                                      float p_interpolationCoefficient)
	{
		if (p_interpolationCoefficient >= 0 && p_interpolationCoefficient <= 1)
			return (p_start + (p_end - p_start) * p_interpolationCoefficient);

		return p_start;
	}

	template <typename T>
	constexpr Vector3<T> Vector3<T>::Slerp(const Vector3<T>& p_start, const Vector3<T>& p_end,
	                                       float p_interpolationCoefficient)
	{
		if (p_interpolationCoefficient >= 0 && p_interpolationCoefficient <= 1)
		{
			const float angle = p_start.AngleBetween(p_end) * p_interpolationCoefficient;
			Vector3<T> relativeVector = p_end - p_start * p_start.DotProduct(p_end);
			relativeVector.Normalize();

			return (p_start * Tools::Utils::Cos(angle) + relativeVector * Tools::Utils::Sin(angle));
		}

		return p_start;
	}

#pragma endregion
#pragma region Conversions

	template <typename T>
	constexpr std::string Vector3<T>::ToString() const
	{
		return std::string("x : " + std::to_string(x) + " y : " + std::to_string(y) + " z : " + std::to_string(z));
	}

	template <typename T>
	constexpr std::string Vector3<T>::ToString(const Vector3<T>& p_vector)
	{
		return p_vector.ToString();
	}

	template <typename T>
	constexpr Vector3<T> Vector3<T>::ToScreenCoordinates(float p_screenWidth, float p_screenHeight) const
	{
		return Vector3<T>((x + 1) * 0.5 * p_screenWidth, p_screenHeight - (y + 1) * 0.5 * p_screenHeight, z);
	}

	template <typename T>
	constexpr Vector3<T> Vector3<T>::ToScreenCoordinates(const Vector3<T>& p_vector, float p_screenWidth,
	                                                     float p_screenHeight)
	{
		return p_vector.ToScreenCoordinates(p_screenWidth, p_screenHeight);
	}

#pragma endregion
#pragma region Outside Operators

	template <typename T>
	constexpr std::ostream& operator<<(std::ostream& p_stream, const AltMath::Vector3<T>& p_vector)
	{
		p_stream << "x : " << p_vector.x << " y : " << p_vector.y << " z : " << p_vector.z;
		return p_stream;
	}

	template <typename T>
	constexpr Vector3<T> operator+(T p_scalar, const Vector3<T>& p_vector)
	{
		return p_vector + p_scalar;
	}

	template <typename T>
	constexpr Vector3<T>& operator+=(T p_scalar, Vector3<T>& p_vector)
	{
		return p_vector += p_scalar;
	}

	template <typename T>
	constexpr Vector3<T> operator-(T p_scalar, const Vector3<T>& p_vector)
	{
		return p_vector - p_scalar;
	}

	template <typename T>
	constexpr Vector3<T>& operator-=(T p_scalar, Vector3<T>& p_vector)
	{
		return p_vector -= p_scalar;
	}

	template <typename T>
	constexpr Vector3<T> operator*(T p_scalar, const Vector3<T>& p_vector)
	{
		return p_vector * p_scalar;
	}

	template <typename T>
	constexpr Vector3<T>& operator*=(T p_scalar, Vector3<T>& p_vector)
	{
		return p_vector *= p_scalar;
	}

	template <typename T>
	constexpr Vector3<T> operator/(T p_scalar, const Vector3<T>& p_vector)
	{
		return p_vector / p_scalar;
	}

	template <typename T>
	constexpr Vector3<T>& operator/=(T p_scalar, Vector3<T>& p_vector)
	{
		return p_vector /= p_scalar;
	}

#pragma endregion
}

#endif //_VECTOR3_H
