/**
 * Project AltMath
 * @author GP2021
 * @version 1.0.0
 */

#pragma once
#ifndef _VECTOR3_H
#define _VECTOR3_H

namespace AltMath
{
    template <typename T>
    struct Vector2;

	template <typename T>
	struct Vector3
	{
		static_assert(std::is_arithmetic<T>::value, "Vector3 should only be used with arithmetic types");

		T x;
		T y;
		T z;

        static const Vector3<T> Zero;
        static const Vector3<T> XAxis;
        static const Vector3<T> YAxis;
        static const Vector3<T> ZAxis;

#pragma region Constructors & Assignment

		/**
		* Default Constructor
		*/
		constexpr Vector3();

		/**
		 * Constructor with parameters
		 * @param p_x
		 * @param p_y
		 * @param p_z
		 */
		constexpr Vector3(T p_x, T p_y, T p_z);

		/**
		* Constructor from vector2
		* @param p_other
		*/
		explicit constexpr Vector3(const Vector2<T>& p_other);

		/**
		* Move Constructor from vector2
		* @param p_other
		*/
		explicit constexpr Vector3(Vector2<T>&& p_other);

		/**
		 * Copy Constructor
		 * @param p_other
		 */
		constexpr Vector3(const Vector3<T>& p_other);

		/**
		 * Move Constructor
		 * @param p_other
		 */
		constexpr Vector3(Vector3<T>&& p_other);

		/**
		 * Overload = operator by copy
		 * @param p_other
		 */
		constexpr Vector3<T>& operator=(const Vector3<T>& p_other);

		/**
		 * Overload = operator by move
		 * @param p_other
		 */
		constexpr Vector3<T>& operator=(Vector3<T>&& p_other);

#pragma endregion
#pragma region Tests & Comparisons

		/**
		* Return true if the two vectors are parallel
		* @param p_other
		*/
		constexpr bool IsParallelTo(const Vector3<T>& p_other) const;

		/**
		* Return true if the two vectors are parallel
		* @param p_left
		* @param p_right
		*/
		constexpr static bool AreParallel(const Vector3<T>& p_left, const Vector3<T>& p_right);

		/**
		* Return true if the two vectors are perpendicular
		* @param p_other
		*/
		constexpr bool IsPerpendicularTo(const Vector3<T>& p_other) const;

		/**
		* Return true if the two vectors are perpendicular
		* @param p_left
		* @param p_right
		*/
		constexpr static bool ArePerpendicular(const Vector3<T>& p_left, const Vector3<T>& p_right);

		/**
		* Return true if the two vectors are identical
		* @param p_other
		*/
		constexpr bool IsEqualTo(const Vector3<T>& p_other) const;

		/**
		* Return true if the two vectors are identical
		* @param p_left
		* @param p_right
		*/
		constexpr static bool AreEqual(const Vector3<T>& p_left, const Vector3<T>& p_right);

		/**
		* Return true if the two vectors are identical
		* @param p_other
		*/
		constexpr bool operator==(const Vector3<T>& p_other) const;

#pragma endregion
#pragma region Arithmetic Operations

#pragma region Add

		/**
		* Add scalar to x, y and z
		* @param p_scalar
		*/
		Vector3<T>& Add(T p_scalar);

		/**
		* Add scalar to vector left
		* @param p_left
		* @param p_scalar
		*/
		constexpr static Vector3<T> Add(const Vector3<T>& p_left, T p_scalar);

		/**
		* Add other vector to the actual vector
		* @param p_other
		*/
		Vector3<T>& Add(const Vector3<T>& p_other);

		/**
		* Add left vector to the right vector
		* @param p_left
		* @param p_right
		*/
		constexpr static Vector3<T> Add(const Vector3<T>& p_left, const Vector3<T>& p_right);

		/**
		* Return the summation of other vector and scalar
		* @param p_scalar
		*/
		constexpr Vector3<T> operator +(T p_scalar) const;

		/**
		* Add scalar to the actual vector
		* @param p_scalar
		*/
		Vector3<T>&  operator+=(T p_scalar);

		/**
		* Return the summation of other vector and actual vector
		* @param p_other
		*/
		constexpr Vector3<T> operator+(const Vector3<T>& p_other) const;

		/**
		* Add other vector to the actual vector
		* @param p_other
		*/
		Vector3<T>& operator+=(const Vector3<T>& p_other);

#pragma endregion
#pragma region Substract

		/**
		* Subtract scalar to x, y and z
		* @param p_scalar
		*/
		Vector3<T>& Subtract(T p_scalar);

		/**
		* Subtract scalar to vector left
		* @param p_left
		* @param p_scalar
		*/
		constexpr static Vector3<T> Subtract(const Vector3<T>& p_left, T p_scalar);

		/**
		* Subtract other vector to the actual vector
		* @param p_other
		*/
		Vector3<T>& Subtract(const Vector3<T>& p_other);

		/**
		* Subtract left vector to the right vector
		* @param p_left
		* @param p_right
		*/
		constexpr static Vector3<T> Subtract(const Vector3<T>& p_left, const Vector3<T>& p_right);

		/**
		* Return the subtraction of other vector and actual vector
		* @param p_scalar
		*/
		constexpr Vector3<T> operator -(T p_scalar) const;

		/**
		* Subtract other vector to the actual vector
		* @param p_scalar
		*/
		Vector3<T>& operator -=(T p_scalar);

		/**
		* Return the subtraction of other vector and actual vector
		* @param p_other
		*/
		constexpr Vector3<T> operator-(const Vector3<T>& p_other) const;

		/**
		* Subtract other vector to the actual vector
		* @param p_other
		*/
		Vector3<T>& operator-=(const Vector3<T>& p_other);

#pragma endregion
#pragma region Multiply

		/**
		* Multiply scalar to x, y and z
		* @param p_scalar
		*/
		Vector3<T>& Multiply(T p_scalar);

		/**
		* Multiply scalar to vector left
		* @param p_left
		* @param p_scalar
		*/
		constexpr static Vector3<T> Multiply(const Vector3<T>& p_left, T p_scalar);

		/**
		* Return the multiplication of scalar and actual vector
		* @param p_scalar
		*/
		constexpr Vector3<T> operator*(T p_scalar) const;

		/**
		* Multiply scalar to the actual vector
		* @param p_scalar
		*/
		Vector3<T>& operator*=(T p_scalar);

#pragma endregion
#pragma region Divide

		/**
		* Divide scalar to x, y and z
		* @param p_scalar
		*/
		Vector3<T>& Divide(T p_scalar);

		/**
		* Divide scalar to vector left
		* @param p_left
		* @param p_scalar
		*/
		constexpr static Vector3<T> Divide(const Vector3<T>& p_left, T p_scalar);

		/**
		* Return the division of scalar and actual vector
		* @param p_scalar
		*/
		constexpr Vector3<T> operator/(T p_scalar) const;

		/**
		* Divide scalar to the actual vector
		* @param p_scalar
		*/
		Vector3<T>& operator/=(T p_scalar);

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
		constexpr static T Length(const Vector3<T>& p_vector);

		/**
		* Calculate the squared length of the vector
		*/
		constexpr T LengthSquare() const;

		/**
		* Calculate the squared length of the vector
		* @param p_vector
		*/
		constexpr static T LengthSquare(const Vector3<T>& p_vector);

		/**
		* Calculate the dot product with other vector
		* @param p_other
		*/
		constexpr T DotProduct(const Vector3<T>& p_other) const;

		/**
		* Calculate the dot product between two vectors
		* @param p_left
		* @param p_right
		*/
		constexpr static T DotProduct(const Vector3<T>& p_left, const Vector3<T>& p_right);

		/**
		* Calculate the cross product with other vector
		* @param p_other
		*/
		constexpr Vector3<T> CrossProduct(const Vector3<T>& p_other) const;

		/**
		* Calculate the cross product between two vectors
		* @param p_left
		* @param p_right
		*/
		constexpr static Vector3<T> CrossProduct(const Vector3<T>& p_left, const Vector3<T>& p_right);

		/**
		* Calculate the dot product between left and the result of cross product between middle and left
		* @param p_left
		* @param p_middle
		* @param p_right
		*/
		constexpr static T TripleProduct(const Vector3<T>& p_left, const Vector3<T>& p_middle, const Vector3<T>& p_right);

		/**
		* Calculate the angle between two vectors in radiant
		* @param p_other
		*/
		constexpr T AngleBetween(const Vector3<T>& p_other) const;

		/**
		* Calculate the angle between two vectors in radiant
		* @param p_left
		* @param p_right
		*/
		constexpr static T AngleBetween(const Vector3<T>& p_left, const Vector3<T>& p_right);

		/**
		* Normalize the vector
		*/
		Vector3<T>& Normalize();


		/**
		* Return the normalized vector
		* @param p_vector
		*/
		constexpr static Vector3<T> Normalize(const Vector3<T>& p_vector);

		/**
		* Return the start vector moving to the end vector at step interpolationCoefficient
		* @param p_start
		* @param p_end
		* @param p_interpolationCoefficient between 0 and 1, 0 is start, 1 is end
		*/
		constexpr static Vector3<T> Lerp(const Vector3<T>& p_start, const Vector3<T>& p_end, float p_interpolationCoefficient);

		/**
		* Return the start vector moving to the end vector at step interpolationCoefficient
		* @param p_start
		* @param p_end
		* @param p_interpolationCoefficient between 0 and 1, 0 is start, 1 is end
		*/
		constexpr static Vector3<T> Slerp(const Vector3<T>& p_start, const Vector3<T>& p_end, float p_interpolationCoefficient);

#pragma endregion
#pragma region Conversions

		/**
		* Convert vector to string
		*/
		constexpr std::string ToString() const;

		/**
		* Convert vector to string
		* @param p_vector
		*/
		constexpr static std::string ToString(const Vector3<T>& p_vector);

		/**
		* Convert vector to screen coordinates
		* @param p_screenWidth
		* @param p_screenHeight
		*/
		constexpr Vector3<T> ToScreenCoordinates(float p_screenWidth, float p_screenHeight) const;

		/**
		* Convert vector to screen coordinates
		* @param p_vector
		* @param p_screenWidth
		* @param p_screenHeight
		*/
		constexpr static Vector3<T> ToScreenCoordinates(const Vector3<T>& p_vector, float p_screenWidth, float p_screenHeight);

#pragma endregion
	};

#pragma region Outside Operators

	template <typename T>
	constexpr std::ostream& operator<<(std::ostream& p_stream, const Vector3<T>& p_vector);

	template <typename T>
	constexpr Vector3<T> operator+(T p_scalar, const Vector3<T>& p_vector);

	template <typename T>
	constexpr Vector3<T>& operator+=(T p_scalar, Vector3<T>& p_vector);

	template <typename T>
	constexpr Vector3<T> operator-(T p_scalar, const Vector3<T>& p_vector);

	template <typename T>
	constexpr Vector3<T>& operator-=(T p_scalar, Vector3<T>& p_vector);

	template <typename T>
	constexpr Vector3<T> operator*(T p_scalar, const Vector3<T>& p_vector);

	template <typename T>
	constexpr Vector3<T>& operator*=(T p_scalar, Vector3<T>& p_vector);

	template <typename T>
	constexpr Vector3<T> operator/(T p_scalar, const Vector3<T>& p_vector);

	template <typename T>
	constexpr Vector3<T>& operator/=(T p_scalar, Vector3<T>& p_vector);

#pragma endregion

	using Vector3F = AltMath::Vector3<float>;
	using Vector3f = AltMath::Vector3<float>;
	using Vector3I = AltMath::Vector3<int>;
	using Vector3i = AltMath::Vector3<int>;
}

#include "Vector3.inl"

#endif //_VECTOR3_H
