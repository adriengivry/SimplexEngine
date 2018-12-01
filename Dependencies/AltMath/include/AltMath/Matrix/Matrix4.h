/**
* Project AltMath
* @author GP2021
* @version 1.0.0
*/

#pragma once
#ifndef _MATRIX4_H
#define _MATRIX4_H
#define EPSILON 0.00001f

#include "AltMath/Vector/Vector4.h"

namespace AltMath
{
	template<typename T>
	struct Vector3;

	template<typename T>
	struct Matrix4
	{
		static_assert(std::is_arithmetic<T>::value, "Matrix4 should only be used with arithmetic types");

		T elements[16];
		static const Matrix4<T> Identity;

#pragma region Constructor & Assignement
        /**     
         * Default constructor, set to Identity Matrix
         */
		Matrix4();

		/**
         * Basic constructor
		 * @param p_element1
		 * @param p_element2
		 * @param p_element3
		 * @param p_element4
		 * @param p_element5
		 * @param p_element6
		 * @param p_element7
		 * @param p_element9
		 * @param p_element8
		 */
		Matrix4(T p_element1,  T p_element2,  T p_element3,  T p_element4,  T p_element5,  T p_element6, 
				T p_element7,  T p_element8,  T p_element9,  T p_element10, T p_element11, T p_element12,
				T p_element13, T p_element14, T p_element15, T p_element16);

		/**
         * Copy Constructor
		 * @param p_other
		 */
		Matrix4(const Matrix4<T>& p_other);

		/**
         * Move Constructor
		 * @param p_other
		 */
		Matrix4(Matrix4<T>&& p_other);

		/**
         * Copy assignment
		 * @param p_other
		 */
		Matrix4<T>& operator=(const Matrix4<T>& p_other);

		/**
         * Move assignment
		 * @param p_other
		 */
		Matrix4<T> operator=(Matrix4<T>&& p_other);
#pragma endregion

#pragma region Arithmetic Operation
		/**
         * Matrix Addition
		 * @param p_other
		 */
		Matrix4<T>& Add(const Matrix4<T>& p_other);

		/**
         * Matrix Addition
		 * @param p_left
		 * @param p_right
		 */
		static Matrix4<T> Add(const Matrix4<T>& p_left, const Matrix4<T>& p_right);

		/**
         * Matrix Addition
		 * @param p_other
		 */
		Matrix4<T> operator+(const Matrix4<T>& p_other) const;

		/**
         * Matrix Addition
		 * @param p_other
		 */
		Matrix4<T>& operator+=(const Matrix4<T>& p_other);

		/**
         * Matrix Subtraction
		 * @param p_other
		 */
		Matrix4<T>& Subtract(const Matrix4<T>& p_other);

		/**
         * Matrix Subtraction
		 * @param p_left
		 * @param p_right
		 */
		static Matrix4<T> Subtract(const Matrix4<T>& p_left, const Matrix4<T>& p_right);

		/**
         * Matrix Subtraction
		 * @param p_other
		 */
		Matrix4<T> operator-(const Matrix4<T>& p_other) const;

		/**
         * Matrix Subtraction
		 * @param p_other
		 */
		Matrix4<T>& operator-=(const Matrix4<T>& p_other);

		/**
         * Scalar Product
		 * @param p_scalar
		 */
		Matrix4<T>& Multiply(T p_scalar);

		/**
         * Scalar Product
		 * @param p_left
		 * @param p_scalar
		 */
		static Matrix4<T> Multiply(const Matrix4<T>& p_left, T p_scalar);

        /**
         * Matrix Product
         * @param p_scalar
         */
        Matrix4<T> operator*(T p_scalar) const;

        /**
         * Matrix Product
         * @param p_scalar
         */
        Matrix4<T>& operator*=(T p_scalar);

		/**
         * Vector Product
		 * @param p_vector
		 */
		Vector4<T> Multiply(const Vector4<T>& p_vector) const;

        /**
         * Vector Product
         * @param p_matrix
         * @param p_vector
         */
		static Vector4<T> Multiply(const Matrix4<T>& p_matrix, const Vector4<T>& p_vector);

        /**
         * Vector Product
         * @param p_vector
         */
        Vector4<T> operator*(const Vector4<T>& p_vector);

        /**
        * Vector Product
        * @param p_vector
        */
        Vector4<T>& operator*=(const Vector4<T>& p_vector);

        /**
         * Matrix Product
         * @param p_other
         */
		Matrix4<T>& Multiply(const Matrix4<T>& p_other);

        /**
         * Matrix Product
         * @param p_left
         * @param p_right
         */
		static Matrix4<T> Multiply(const Matrix4<T>& p_left, const Matrix4<T>& p_right);

        /**
         * Matrix Product
         * @param p_other
         */
	    Matrix4<T> operator*(const Matrix4<T>& p_other) const;

        /**
         * Matrix Product
         * @param p_other
         */
		Matrix4<T>& operator*=(const Matrix4<T>& p_other);

		/**
         * Scalar Division
		 * @param p_scalar
		 */
		Matrix4<T> Divide(T p_scalar);

		/**
         * Scalar Division
		 * @param p_left
		 * @param p_scalar
		 */
		static Matrix4<T> Divide(const Matrix4<T>& p_left, T p_scalar);

		/**
         * Scalar Division
		 * @param p_scalar
		 */
		Matrix4<T> operator/(T p_scalar) const;

        /**
         * Scalar Division
         * @param p_scalar
         */
        Matrix4<T>& operator/=(T p_scalar);

        /**
         * Matrix Division
         * @param p_other
         */
		Matrix4<T> Divide(const Matrix4<T>& p_other);

        /**
         * Matrix Division
         * @param p_left
         * @param p_right
         */
		static Matrix4<T> Divide(const Matrix4<T>& p_left, const Matrix4<T>& p_right);
        
        /**
        * Matrix Division
        * @param p_other
        */
		Matrix4<T> operator/(const Matrix4<T>& p_other) const;
        
        /**
        * Matrix Division
        * @param p_other
        */
		Matrix4<T>& operator/=(const Matrix4<T>& p_other);

#pragma endregion

#pragma region Matrix Operation

		static float GetMinor(float p_minor0, float p_minor1, float p_minor2, float p_minor3, float p_minor4, float p_minor5,
			                    float p_minor6, float p_minor7, float p_minor8);

		T Determinant();

		/**
		* @param p_matrix
		*/
		static T Determinant(const Matrix4<T>& p_matrix);

		Matrix4<T> Inverse() const;

		/**
		* @param p_matrix
		*/
		static const Matrix4<T> Inverse(const Matrix4<T>& p_matrix);

        Matrix4<T>& Transpose();

		/**
		* @param p_matrix
		*/
		static Matrix4<T> Transpose(const Matrix4<T>& p_matrix);

		bool IsIdentity();
		/* @param p_translation
		*/
		static constexpr Matrix4<T> Translation(const Vector3<T>& p_translation);

		/**
		* @param p_matrix
		* @param p_translation
		*/
		static constexpr Matrix4<T> Translate(const Matrix4<T>& p_matrix, const Vector3<T>& p_translation);

		/**
		* @param p_translation
		*/
		Matrix4<T>& Translate(const Vector3<T>& p_translation);

		/**
		* @param p_rotation
		*/
		static constexpr Matrix4<T> RotationOnAxisX(float p_rotation);

		/**
		* @param p_matrix
		* @param p_rotation
		*/
		static constexpr Matrix4<T> RotateOnAxisX(const Matrix4<T>& p_matrix, float p_rotation);

		/**
		* @param p_rotation
		*/
		Matrix4<T>& RotateOnAxisX(float p_rotation);

		static constexpr Matrix4<T> RotationOnAxisY(float p_rotation);

		/**
		* @param p_matrix
		* @param p_rotation
		*/
		static constexpr Matrix4<T> RotateOnAxisY(const Matrix4<T>& p_matrix, float p_rotation);

		/**
		* @param p_rotation
		*/
		Matrix4<T>& RotateOnAxisY(float p_rotation);


		static constexpr Matrix4<T> RotationOnAxisZ(float p_rotation);

		/**
		* @param p_matrix
		* @param p_rotation
		*/
		static constexpr Matrix4<T> RotateOnAxisZ(const Matrix4<T>& p_matrix, float p_rotation);

		/**
		* @param p_rotation
		*/
		Matrix4<T>& RotateOnAxisZ(float p_rotation);


		static constexpr Matrix4<T> RotationYXZ(float p_rotation);

		/**
		* @param p_matrix
		* @param p_rotation
		*/
		static constexpr Matrix4<T> RotateYXZ(const Matrix4<T>& p_matrix, float p_rotation);

		/**
		* @param p_rotation
		*/
		Matrix4<T>& RotateYXZ(float p_rotation);
		/**
		* @param p_scale
		*/
		static constexpr Matrix4<T> Scaling(const Vector3<T>& p_scale);

		/**
		* @param p_matrix
		* @param p_scale
		*/
		static constexpr Matrix4<T> Scale(const Matrix4<T>& p_matrix, const Vector3<T>& p_scale);

		/**
		* @param p_scale
		*/
		Matrix4<T>& Scale(const Vector3<T>& p_scale);

		static Matrix4<float> CreatePerspective(const float p_fov, const float p_aspectRatio, const float p_zNear, const float p_zFar);
		static Matrix4<float> CreateView(const float p_eyeX, const float p_eyeY, const float p_eyeZ, const float p_lookX, const float p_lookY, const float p_lookZ, const float p_upX, const float p_upY, const float p_upZ);
		static Matrix4<float> CreateFrustum(const float p_left, const float p_right, const float p_bottom, const float p_top, const float p_zNear, const float p_zFar);
#pragma endregion

#pragma region Comparison & Conversion & Test
		/**
		* Get element at index (row,column)
		* @param p_row
		* @param p_column
		*/
		T& operator()(uint8_t p_row, uint8_t p_column);

		std::string ToString() const;
		static std::string ToString(const Matrix4<T>& p_matrix);
        
        /**
         * Return 1D-array of matrix
         * @param p_matrix
         */
		T* ToArray();

		/**
         * Return 1D-array of matrix
		 * @param p_matrix
		 */
		static T* ToArray(const Matrix4<T>& p_matrix);

		Vector4<T> GetRow(uint8_t p_row);

		Vector4<T> GetColumn(uint8_t p_column);
#pragma endregion
	};
    /**
    * @param p_stream
    * @param p_matrix
    */
    template<typename T>
    std::ostream& operator<<(std::ostream& p_stream, const Matrix4<T>& p_matrix);

    using Matrix4F = AltMath::Matrix4<float>;
    using Matrix4f = AltMath::Matrix4<float>;
    using Matrix4I = AltMath::Matrix4<int>;
    using Matrix4i = AltMath::Matrix4<int>;
}
#include "Matrix4.inl"

#endif //_MATRIX4_H