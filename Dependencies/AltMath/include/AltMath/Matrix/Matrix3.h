/**
 * Project AltMath
 * @author GP2021
 * @version 1.0.0
 */

#pragma once
#ifndef _MATRIX3_H
#define _MATRIX3_H

namespace AltMath
{
    template<typename T>
    struct Matrix2;
    template<typename T>
    struct Vector2;




	template<typename T >
	struct Matrix3 
	{	
		static_assert(std::is_arithmetic<T>::value, "Matrix3 should only be used with arithmetic types");

		T elements[9];
		static const Matrix3<T> Identity;
		static const Matrix3<T> Zero;

#pragma region Constructor & Assignement

	    /**
		 * Default-constructor, sets matrix to 0
		 */
		constexpr Matrix3();

		/**
		 * Set all elements to value
		 * @param p_value
		 */
        explicit constexpr Matrix3(T p_value);

		/**
		 * Constructor
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
		constexpr Matrix3(T p_element1, T p_element2, T p_element3, T p_element4, T p_element5, T p_element6, T p_element7, T p_element8, T p_element9);

		/**
		 * Copy constructor
		 * @param p_other
		 */
		constexpr Matrix3(const Matrix3<T>& p_other);

		/**
		 * Move Constructor
		 * @param p_other
		 */
		Matrix3(Matrix3<T>&& p_other) noexcept;

        /**
         * Constructor from Matrix2
		 * @param p_matrix2
		 */
	    explicit constexpr Matrix3(const Matrix2<T>& p_matrix2);

		/**
		 * Copy assignment
		 * @param p_other
		 */
		Matrix3<T>& operator=(const Matrix3<T>& p_other);

		/**
		 * Move Assignment
		 * @param p_other
		 */
		Matrix3<T>& operator=(Matrix3<T>&& p_other) noexcept;

#pragma endregion

#pragma region Tests & Comparisons

        /**
		 * Compare to Identity matrix
		 */
		constexpr bool IsIdentity();

        /**
         * Check if elements are equals 
		 * @param p_other
		 */
		constexpr bool IsEqualTo(const Matrix3<T>& p_other);

		/**
		 * Check if elements are equals 
		 * @param p_left
		 * @param p_right
		 */
		static constexpr bool AreEquals(const Matrix3<T>& p_left, const Matrix3<T>& p_right);

		/**
		 * Check if elements are equals 
		 * @param p_other
		 */
		constexpr bool operator==(const Matrix3<T>& p_other);

#pragma endregion

#pragma region Arithmetic Operations
    #pragma region Addition
		/**
		 * Element-wise addition
		 * @param p_scalar
		 */
		Matrix3<T>& Add(T p_scalar);

		/**
		 * Element-wise addition
		 * @param p_left
		 * @param p_scalar
		 */
		static Matrix3<T> Add(const Matrix3<T>& p_left, T p_scalar);

		/**
		 * Element-wise addition
		 * @param p_other
		 */
		Matrix3<T>& Add(const Matrix3<T>& p_other);

		/**
		 * Element-wise addition
		 * @param p_left
		 * @param p_right
		 */
		static constexpr Matrix3<T> Add(const Matrix3<T>& p_left, const Matrix3<T>& p_right);

		/**
		 * Element-wise addition
		 * @param p_other
		 */
		constexpr Matrix3<T> operator+(const Matrix3<T>& p_other) const;

		/**
		 * Element-wise addition
		 * @param p_other
		 */
		Matrix3<T>& operator+=(const Matrix3<T>& p_other);
    #pragma endregion
		
    #pragma region Subtraction
	    /**
	     * Element-wise subtraction
		 * @param p_scalar
		 */
		Matrix3<T>& Subtract(T p_scalar);

		/**
		 * Element-wise subtraction
		 * @param p_left
		 * @param p_scalar
		 */
		static constexpr Matrix3<T> Subtract(const Matrix3<T>& p_left, T p_scalar);

		/**
		 * Element-wise subtraction
		 * @param p_other
		 */
		Matrix3<T>& Subtract(const Matrix3<T>& p_other);

		/**
		 * Element-wise subtractions
		 * @param p_left
		 * @param p_right
		 */
		static constexpr Matrix3<T> Subtract(const Matrix3<T>& p_left, const Matrix3<T>& p_right);

		/**
		 * Element-wise subtraction
		 * @param p_other
		 */
		constexpr Matrix3<T> operator-(const Matrix3<T>& p_other) const;

		/**
		 * Element-wise subtraction
		 * @param p_other
		 */
		Matrix3<T>& operator-=(const Matrix3<T>& p_other);
    #pragma endregion

    #pragma region Scalar Product
		/**
		 * Scalar Product
		 * @param p_scalar
		 */
		Matrix3<T>& Multiply(T p_scalar);

		/**
		 * Scalar Product
		 * @param p_left
		 * @param p_scalar
		 */
		static constexpr Matrix3<T> Multiply(const Matrix3<T>& p_left, T p_scalar);
        
		/**
		 * Scalar Product
		 * @param p_scalar
		 */
		constexpr Matrix3<T> operator*(T p_scalar) const;

		/**
		 * Scalar Product
		 * @param p_scalar
		 */
		Matrix3<T>& operator*=(T p_scalar);
    #pragma endregion

    #pragma region Vector Product

        /**
         * Vector Product
		 * @param p_vector
		 */
		constexpr Vector3<T> Multiply(const Vector3<T>& p_vector) const;
		/**
		 * Vector Product
		 * @param p_matrix
		 * @param p_vector
		 */
		static constexpr Vector3<T> Multiply(const Matrix3<T>& p_matrix, const Vector3<T>& p_vector);

		/**
		 * Vector Product
		 * @param p_vector
		 */
		constexpr Vector3<T> operator*(const Vector3<T>& p_vector) const;

    #pragma endregion

    #pragma region Matrix Product
        /**
         * Matrix Product
		 * @param p_other
		 */
		Matrix3<T>& Multiply(const Matrix3<T>& p_other);

		/**
		 * Matrix Product
		 * @param p_left
		 * @param p_right
		 */
		static constexpr Matrix3<T> Multiply(const Matrix3<T>& p_left, const Matrix3<T>& p_right);

        /**
         * Matrix Product
		 * @param p_other
		 */
		constexpr Matrix3<T> operator*(const Matrix3<T>& p_other) const;

        /**
         * Matrix Product
		 * @param p_other
		 */
		Matrix3<T>& operator*=(const Matrix3<T>& p_other);

    #pragma endregion

    #pragma region Scalar Division
		/**
		 * Scalar Division
		 * @param p_scalar
		 */
		constexpr Matrix3<T>& Divide(T p_scalar);

		/**
		 * Scalar Division
		 * @param p_left
		 * @param p_scalar
		 */
		static constexpr Matrix3<T> Divide(const Matrix3<T>& p_left, T p_scalar);

		/**
		 * Scalar Division
		 * @param p_scalar
		 */
		constexpr Matrix3<T> operator/(T p_scalar) const;

		/**
		 * Scalar Division
		 * @param p_scalar
		 */
		Matrix3<T>& operator/=(T p_scalar);
    #pragma endregion

    #pragma region Matrix Division

        /**
		 * Matrix Division
		 * @param p_other
		 */
		Matrix3<T>& Divide(const Matrix3<T>& p_other);

        /**
		 * Matrix Division
		 * @param p_left
		 * @param p_right
		 */
		static constexpr Matrix3<T> Divide(const Matrix3<T>& p_left, const Matrix3<T>& p_right);

        /**
		 * Matrix Division
		 * @param p_other
		 */
		constexpr Matrix3<T> operator/(const Matrix3<T>& p_other) const;

        /**
		 * Matrix Division
		 * @param p_other
		 */
		Matrix3<T>& operator/=(const Matrix3<T>& p_other);
    #pragma endregion
#pragma endregion

#pragma region Matrix Operations
        /**
		 * Compute matrix determinant
		 */
		constexpr T Determinant() const;

		/**
		 * Compute matrix determinant
		 * @param p_matrix
		 */
		static constexpr T Determinant(const Matrix3<T>& p_matrix);

        /**
         * Transpose matrix
         */
        Matrix3<T>& Transpose();

		/**
		 * Return transposed matrix
		 * @param p_matrix
		 */
		static constexpr Matrix3<T> Transpose(const Matrix3<T>& p_matrix);

        /**
         * Return Cofactor matrix
         */
		constexpr Matrix3<T> Cofactor() const;

        /**
		 * Return Cofactor matrix
		 * @param p_matrix
		 */
		static constexpr Matrix3<T> Cofactor(const Matrix3<T>& p_matrix);
        
	    /**
         * Return Minor matrix
         */
		constexpr Matrix3<T> Minor() const;

        /**
		 * Return Minor matrix
		 * @param p_matrix
		 */
		static constexpr Matrix3<T> Minor(const Matrix3<T>& p_matrix);
        
	    /**
         * Return Adjoint matrix
         */
		constexpr Matrix3<T> Adjoint() const;

		/**
		 * Return Adjoint matrix
		 * @param p_other
		 */
		static constexpr Matrix3<T> Adjoint(const Matrix3<T>& p_other);
        
        /**
		 * Return inverse matrix
		 */
		constexpr Matrix3<T> Inverse() const;

		/**
		 * Return inverse matrix
		 * @param p_matrix
		 */
		static constexpr Matrix3<T> Inverse(const Matrix3<T>& p_matrix);

		/**
		 * Return 2D translation matrix
		 * @param p_translation
		 */
		static constexpr Matrix3<T> Translation(const Vector2<T>& p_translation);

		/**
		 * Translate matrix in 2D
		 * @param p_matrix
		 * @param p_translation
		 */
		static constexpr Matrix3<T> Translate(const Matrix3<T>& p_matrix, const Vector2<T>& p_translation);

		/**
		 * Translate matrix in 2D
		 * @param p_translation
		 */
		Matrix3<T>& Translate(const Vector2<T>& p_translation);

		/**
		 * Return 2D rotation matrix
		 * @param p_rotation angle in radians
		 */
		static constexpr Matrix3<T> Rotation(float p_rotation);

		/**
		 * Rotate matrix in 2D
		 * @param p_matrix
		 * @param p_rotation angle in radians
		 */
		static constexpr Matrix3<T> Rotate(const Matrix3<T>& p_matrix, float p_rotation);

		/**
		 * Rotate matrix in 2D
		 * @param p_rotation angle in radians
		 */
		Matrix3<T>& Rotate(float p_rotation);

		/**
		 * Return 2D scaling matrix
		 * @param p_scale
		 */
		static constexpr Matrix3<T> Scaling(const Vector2<T>& p_scale);

		/**
		 * Scale matrix in 2D
		 * @param p_matrix
		 * @param p_scale
		 */
		static constexpr Matrix3<T> Scale(const Matrix3<T>& p_matrix, const Vector2<T>& p_scale);

		/**
		 * Scale matrix in 2D
		 * @param p_scale
		 */
		Matrix3<T>& Scale(const Vector2<T>& p_scale);
#pragma endregion

#pragma region Conversions & Accessors

        /**
         * Get element at index (row,column)
		 * @param p_row
		 * @param p_column
		 */
		T& operator()(uint8_t p_row, uint8_t p_column);

        /**
         * Get row
		 * @param p_row
		 */
		constexpr Vector3<T> GetRow(uint8_t p_row) const;

        /**
         * Get Column
		 * @param p_column
		 */
		constexpr Vector3<T> GetColumn(uint8_t p_column) const;


	    /**
		 * Return elements 1D-array
		 */
		constexpr T* ToArray();

		/**
		 * Return elements 1D-array
		 * @param p_matrix
		 */
		static constexpr T* ToArray(const Matrix3<T>& p_matrix);

        /**
	     * Return formatted string
		 */
		std::string ToString();
	    
	    /**
	     * Return formatted string
		 * @param p_matrix
		 */
		static std::string ToString(const Matrix3<T>& p_matrix);


#pragma endregion
	};

	template <typename T>
	std::ostream& operator<<(std::ostream& p_stream, const Matrix3<T>& p_matrix);

    using Matrix3F = AltMath::Matrix3<float>;
	using Matrix3f = AltMath::Matrix3<float>;
	using Matrix3I = AltMath::Matrix3<int>;
	using Matrix3i = AltMath::Matrix3<int>;
}
#include "Matrix3.inl"

#endif //_MATRIX3_H