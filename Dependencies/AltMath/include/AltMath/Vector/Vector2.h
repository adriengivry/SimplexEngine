/**
 * Project AltMath
 * @author GP2021
 * @version 1.0.0
 */

#pragma once
#ifndef _VECTOR2_H
#define _VECTOR2_H

#include <iostream>
#include <string>

namespace AltMath
{
	 
	template <typename T>
	struct Vector2
	{
		static_assert(std::is_arithmetic<T>::value, "Vector2 should only be used with arithmetic types");

		T x;
		T y;

		static constexpr Vector2<T> Zero();

#pragma region Constructors & Assignment
		/**
		 * Default Constructor
		 */
		constexpr Vector2();

		/**
		 * Constructor with parameters 
		 * @param p_x
		 * @param p_y
		 */
		constexpr Vector2(T p_x, T p_y);

		/**
		 * Copy Constructor 
		 * @param p_other
		 */
		constexpr Vector2(const Vector2<T>& p_other);

		/**
		 * Move Constructor
		 * @param p_other
		 */
		constexpr Vector2(Vector2<T>&& p_other);

		/**
		 * Overload = operator by copy
		 * @param p_other
		 */
		constexpr Vector2<T>& operator=(const Vector2<T>& p_other);

		/**
		 * Overload = operator by move
		 * @param p_other
		 */
		constexpr Vector2<T>& operator=(Vector2<T>&& p_other);

#pragma endregion

#pragma region Tests & Comparisons

		/**
		* Return true if the two vectors are parallel
		* @param p_other
		*/
		constexpr bool IsParallelTo(const Vector2<T>& p_other) const;

		/**
		* Return true if the two vectors are parallel
		* @param p_left
		* @param p_right
		*/
		constexpr static bool AreParallel(const Vector2<T>& p_left, const Vector2<T>& p_right);

		/**
		* Return true if the two vectors are perpendicular
		* @param p_other
		*/
		constexpr bool IsPerpendicularTo(const Vector2<T>& p_other) const;

		/**
		* Return true if the two vectors are perpendicular
		* @param p_left
		* @param p_right
		*/
		constexpr static bool ArePerpendicular(const Vector2<T>& p_left, const Vector2<T>& p_right);

		/**
		* Return true if the two vectors are identical
		* @param p_other
		*/
		constexpr bool IsEqualTo(const Vector2<T>& p_other) const;

		/**
		* Return true if the two vectors are identical
		* @param p_left
		* @param p_right
		*/
		constexpr static bool AreEqual(const Vector2<T>& p_left, const Vector2<T>& p_right);

		/**
		* Return true if the two vectors are identical
		* @param p_other
		*/
		constexpr bool operator==(const Vector2<T>& p_other) const;

#pragma endregion

#pragma region Arithmetic Operations

#pragma region Add

		/**
		 * Add scalar to x and y
		 * @param p_scalar
		 */
		Vector2<T>& Add(T p_scalar);

		/**
		 * Add scalar to vector left
		 * @param p_left
		 * @param p_scalar
		 */
		constexpr static Vector2<T> Add(const Vector2<T>& p_left, T p_scalar);

		/**
		 * Add other vector to the actual vector
		 * @param p_other
		 */
		Vector2<T>& Add(const Vector2<T>& p_other);

		/**
		 * Add left vector to the right vector
		 * @param p_left
		 * @param p_right
		 */
		constexpr static Vector2<T> Add(const Vector2<T>& p_left, const Vector2<T>& p_right);

		/**
		 * Return the summation of other vector and scalar
		 * @param p_scalar
		 */
		constexpr Vector2<T> operator +(T p_scalar) const;

		/**
		 * Add scalar to the actual vector
		 * @param p_scalar
		 */
		Vector2<T>&  operator+=(T p_scalar);

		/**
		* Return the summation of other vector and actual vector
		* @param p_other
		*/
		constexpr Vector2<T> operator +(const Vector2<T>& p_other) const;

		/**
		* Add other vector to the actual vector
		* @param p_other
		*/
		Vector2<T>&  operator+=(const Vector2<T>& p_other);

#pragma endregion

#pragma region Substract

		/**
		 * Subtract scalar to x and y
		 * @param p_scalar
		 */
		Vector2<T>& Subtract(T p_scalar);

		/**
		 * Subtract scalar to vector left
		 * @param p_left
		 * @param p_scalar
		 */
		constexpr static Vector2<T> Subtract(const Vector2<T>& p_left, T p_scalar);

		/**
		 * Subtract other vector to the actual vector
		 * @param p_other
		 */
		Vector2<T>& Subtract(const Vector2<T>& p_other);

		/**
		 * Subtract left vector to the right vector
		 * @param p_left
		 * @param p_right
		 */
		constexpr static Vector2<T> Subtract(const Vector2<T>& p_left, const Vector2<T>& p_right);

		/**
		* Return the subtraction of other vector and actual vector
		* @param p_scalar
		*/
		constexpr Vector2<T> operator -(T p_scalar) const;

		/**
		* Subtract other vector to the actual vector
		* @param p_scalar
		*/
		Vector2<T>& operator -=(T p_scalar);

		/**
		 * Return the subtraction of other vector and actual vector
		 * @param p_other
		 */
		constexpr Vector2<T> operator -(const Vector2<T>& p_other) const;

		/**
		 * Subtract other vector to the actual vector
		 * @param p_other
		 */
		Vector2<T>& operator -=(const Vector2<T>& p_other);

#pragma endregion

#pragma region Multiply

		/**
		 * Multiply scalar to x and y
		 * @param p_scalar
		 */
		Vector2<T>& Multiply(T p_scalar);

		/**
		 * Multiply scalar to vector left
		 * @param p_left
		 * @param p_scalar
		 */
		constexpr static Vector2<T> Multiply(const Vector2<T>& p_left, T p_scalar);

		/**
		 * Return the multiplication of scalar and actual vector
		 * @param p_scalar
		 */
		constexpr Vector2<T> operator *(T p_scalar) const;

		/**
		 * Multiply scalar to the actual vector
		 * @param p_scalar
		 */
		Vector2<T>& operator *=(T p_scalar);

#pragma endregion

#pragma region Divide

		/**
		 * Divide scalar to x and y
		 * @param p_scalar
		 */
		Vector2<T>& Divide(T p_scalar);

		/**
		 * Divide scalar to vector left
		 * @param p_left
		 * @param p_scalar
		 */
		constexpr static Vector2<T> Divide(const Vector2<T>& p_left, T p_scalar);

		/**
		 * Return the division of scalar and actual vector
		 * @param p_scalar
		 */
		constexpr Vector2<T> operator /(T p_scalar) const;

		/**
		 * Divide scalar to the actual vector
		 * @param p_scalar
		 */
		Vector2<T>& operator /=(T p_scalar);

#pragma endregion

#pragma endregion

#pragma region Vector Operations

		/**
		* Calculate the length of the vector
		*/
		constexpr T Length() const;

		/**
		* Calculate the length of the vector
		* @param p_vector
		*/
		constexpr static T Length(const Vector2<T>& p_vector);

		/**
		* Calculate the squared length of the vector
		*/
		constexpr T LengthSquare() const;

		/**
		* Calculate the squared length of the vector
		* @param p_vector
		*/
		constexpr static T LengthSquare(const Vector2<T>& p_vector);

		/**
		 * Calculate the dot product with other vector
		 * @param p_other	 
		 */
		constexpr T DotProduct(const Vector2<T>& p_other) const;

		/**
		* Calculate the dot product between two vectors
		* @param p_left
		* @param p_right
		*/
		constexpr static T DotProduct(const Vector2<T>& p_left, const Vector2<T>& p_right);

		/**
		* Calculate the angle between two vectors in radiant
		* @param p_other
		*/
		constexpr T AngleBetween(const Vector2<T>& p_other) const;

		/**
		* Calculate the angle between two vectors in radiant
		* @param p_left
		* @param p_right
		*/
		constexpr static T AngleBetween(const Vector2<T>& p_left, const Vector2<T>& p_right);

		/**
		 * Normalize the vector
		 */
		Vector2<T>& Normalize();

		/**
		 * Return the normalized vector
		 * @param p_vector
		 */
		constexpr static Vector2<T> Normalize(const Vector2<T>& p_vector);

		/**
		 * Return the start vector moving to the end vector at step interpolationCoefficient
		 * @param p_start
		 * @param p_end
		 * @param p_interpolationCoefficient between 0 and 1, 0 is start, 1 is end
		 */
		constexpr static Vector2<T> Lerp(const Vector2<T>& p_start, const Vector2<T>& p_end, float p_interpolationCoefficient);

		/**
		 * Return the start vector moving to the end vector at step interpolationCoefficient
		 * @param p_start
		 * @param p_end
		 * @param p_interpolationCoefficient between 0 and 1, 0 is start, 1 is end
		 */
		constexpr static Vector2<T> Slerp(const Vector2<T>& p_start, const Vector2<T>& p_end, float p_interpolationCoefficient);

#pragma endregion

#pragma region Conversions

		/**
		 * Convert vector to string
		 */
		constexpr std::string ToString() const;

#pragma endregion
	};

#pragma region Outside Operators

	template <typename T>
	constexpr std::ostream& operator<<(std::ostream& p_stream, const Vector2<T>& p_vector);

	template <typename T>
	constexpr Vector2<T> operator+(T p_scalar, const Vector2<T>& p_vector);

	template <typename T>
	constexpr Vector2<T>& operator+=(T p_scalar, Vector2<T>& p_vector);

	template <typename T>
	constexpr Vector2<T> operator-(T p_scalar, const Vector2<T>& p_vector);

	template <typename T>
	constexpr Vector2<T>& operator-=(T p_scalar, Vector2<T>& p_vector);

	template <typename T>
	constexpr Vector2<T> operator*(T p_scalar, const Vector2<T>& p_vector);

	template <typename T>
	constexpr Vector2<T>& operator*=(T p_scalar, Vector2<T>& p_vector);

	template <typename T>
	constexpr Vector2<T> operator/(T p_scalar, const Vector2<T>& p_vector);

	template <typename T>
	constexpr Vector2<T>& operator/=(T p_scalar, Vector2<T>& p_vector);

#pragma endregion

	using Vector2F = Vector2<float>;
    using Vector2f = Vector2<float>;
    using Vector2I = Vector2<int>;
    using Vector2i = Vector2<int> ;
}

#include "Vector2.inl"

#endif //_VECTOR2_H