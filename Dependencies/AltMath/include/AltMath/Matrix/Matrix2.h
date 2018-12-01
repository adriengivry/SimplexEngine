/**
 * Project AltMath
 * @author GP2021
 * @version 1.0.0
 */

#pragma once
#ifndef _MATRIX2_H
#define _MATRIX2_H

namespace AltMath
{

	template<typename T >
	struct Matrix2 
	{
		static_assert(std::is_arithmetic<T>::value, "Matrix2 should only be used with arithmetic types");

		T elements[4];
		static const Matrix2<T> Identity;
		static const Matrix2<T> Zero;

    #pragma region Constructors & Assignment
		
	    /**
	     * Sets matrix to 0
	     */
	    Matrix2();

		/**
		 * Sets all element to p_value
		 * @param p_value
		 */
		explicit Matrix2(T p_value);

		/**
		 * @param p_element1
		 * @param p_element2
		 * @param p_element3
		 * @param p_element4
		 */
		Matrix2(T p_element1, T p_element2, T p_element3, T p_element4);

		/**
		 * @param p_other
		 */
		Matrix2(const Matrix2<T>& p_other);

        
		/**
		 * @param p_other
		 */
		Matrix2(Matrix2<T>&& p_other) noexcept;

		/**
		 * @param p_other
		 */
		Matrix2<T>& operator=(const Matrix2<T>& p_other);

		/**
		 * @param p_other
		 */
		Matrix2<T>& operator=(Matrix2<T>&& p_other) noexcept;
    #pragma endregion

    #pragma region Tests & Comparisons
	    /** 
         * Compare Matrix with Identity Matrix
         */
        bool IsIdentity() const;

	    /**
	     * Compare matrix memory content
         * @param p_other 
         */
        bool operator==(Matrix2<T>& p_other) const;

    #pragma endregion

    #pragma region Arithmetic Operations
        #pragma region Addition
		/**
		 * Element-wise addition
		 * @param p_scalar
		 */
		Matrix2<T>& Add(T p_scalar);

		/**
		 * Element-wise addition
		 * @param p_left
		 * @param p_scalar
		 */
		static Matrix2<T> Add(const Matrix2<T>& p_left, T p_scalar);

		/**
		 * Element-wise addition
		 * @param p_other
		 */
		Matrix2<T>& Add(const Matrix2<T>& p_other);

		/**
		 * Element-wise addition
		 * @param p_left
		 * @param p_right
		 */
		static Matrix2<T> Add(const Matrix2<T>& p_left, const Matrix2<T>& p_right);

		/**
		 * Element-wise addition
		 * @param p_other
		 */
		Matrix2<T> operator+(const Matrix2<T>& p_other) const;

		/**
		 * Element-wise addition
		 * @param p_other
		 */
		Matrix2<T>& operator+=(const Matrix2<T>& p_other);

        #pragma endregion

        #pragma region Subtraction
	    /**
	     * Element-wise subtraction
		 * @param p_scalar
		 */
		Matrix2<T>& Subtract(T p_scalar);

		/**
		 * Element-wise subtraction
		 * @param p_left
		 * @param p_scalar
		 */
		static Matrix2<T> Subtract(const Matrix2<T>& p_left, T p_scalar);

		/**
		 * Element-wise subtraction
		 * @param p_other
		 */
		Matrix2<T>& Subtract(const Matrix2<T>& p_other);

		/**
		 * Element-wise subtraction
		 * @param p_left
		 * @param p_right
		 */
		static Matrix2<T> Subtract(const Matrix2<T>& p_left, const Matrix2<T>& p_right);

		/**
		 * Element-wise subtraction
		 * @param p_other
		 */
		Matrix2<T> operator-(const Matrix2<T>& p_other) const;

		/**
		 * Element-wise subtraction
		 * @param p_other
		 */
		Matrix2<T>& operator -=(const Matrix2<T>& p_other);

        #pragma endregion
		
	    #pragma region Scalar Product
	    /**
	     * Element-wise multiplication
		 * @param p_scalar
		 */
		Matrix2<T>& Multiply(T p_scalar);

		/**
		 * Element-wise multiplication
		 * @param p_left
		 * @param p_scalar
		 */
		static Matrix2<T> Multiply(const Matrix2<T>& p_left, T p_scalar);

        /**
         * Element-wise multiplication
		 * @param p_scalar
		 */
		Matrix2<T> operator*(T p_scalar) const;

		/**
		 * Element-wise multiplication
		 * @param p_scalar
		 */
		Matrix2<T>& operator*=(T p_scalar);

        #pragma endregion 
		
	    #pragma region Vector Product
	    /**
		 * Matrix-Vector product
		 * @param p_vector
		 */
		Vector2<T> Multiply(const Vector2<T>& p_vector) const;
        
		/**
		 * Matrix-Vector product
		 * @param p_matrix
		 * @param p_vector
		 */
		static Vector2<T> Multiply(const Matrix2<T>& p_matrix, const Vector2<T>& p_vector);
        
		/**
		 * Matrix-Vector product
		 * @param p_vector
		 */
		Vector2<T> operator*(const Vector2<T>& p_vector) const;

        #pragma endregion 

        #pragma region Matrix Product
        /**
		 * Matrix product
		 * @param p_other
		 */
		Matrix2<T>& Multiply(const Matrix2<T>& p_other);

		/**
		 * Matrix product
		 * @param p_left
		 * @param p_right
		 */
		static Matrix2<T> Multiply(const Matrix2<T>& p_left, const Matrix2<T>& p_right);

        /**
		 * Matrix product
		 * @param p_other
		 */
		Matrix2<T> operator*(const Matrix2<T>& p_other) const;

        /**
		 * Matrix product
		 * @param p_other
		 */
		Matrix2<T>& operator*=(const Matrix2<T>& p_other);

        #pragma endregion 

        #pragma region Scalar Division
		/**
		 * Element-wise division
		 * @param p_scalar
		 */
		Matrix2<T>& Divide(T p_scalar);

		/**
		 * Element-wise division
		 * @param p_left
		 * @param p_scalar
		 */
		static Matrix2<T> Divide(const Matrix2<T>& p_left, T p_scalar);

		/**
		 * Element-wise division
		 * @param p_scalar
		 */
		Matrix2<T> operator/(T p_scalar) const;

		/**
		 * Element-wise division
		 * @param p_scalar
		 */
		Matrix2<T>& operator/=(T p_scalar);

        #pragma endregion

        #pragma region Matrix Division

        /**
		 * Matrix division
		 * @param p_other
		 */
		Matrix2<T>& Divide(const Matrix2<T>& p_other);

        /**
		 * Matrix division
		 * @param p_left
		 * @param p_right
		 */
        static Matrix2<T> Divide(const Matrix2<T>& p_left, const Matrix2<T>& p_right);

        /**
		 * Matrix division
		 * @param p_other
		 */
		Matrix2<T> operator/(const Matrix2<T>& p_other);

        /**
		 * Matrix division
		 * @param p_other
		 */
		Matrix2<T>& operator /=(const Matrix2<T>& p_other);

        #pragma endregion
    #pragma endregion

    #pragma region Matrix Operations

        /**
		 * Compute Matrix determinant
		 */
		T Determinant() const;

		/**
		 * Compute Matrix determinant
		 */
		static T Determinant(const Matrix2<T>& p_matrix);

        /**
         * Transpose matrix
         */
        Matrix2<T>& Transpose();

		/**
		 * Return transposed matrix
		 * @param p_matrix
		 */
		static constexpr Matrix2<T> Transpose(const Matrix2<T>& p_matrix);

        /**
         * Return Cofactor matrix
         */
		constexpr Matrix2<T> Cofactor() const;

        /**
		 * Return Cofactor matrix
		 * @param p_matrix
		 */
		static constexpr Matrix2<T> Cofactor(const Matrix2<T>& p_matrix);
        
        /**
		 * Return adjoint Matrix
		 */
		Matrix2<T> Adjoint() const;
        
        /**
		 * Return adjoint Matrix 
		 */
		static Matrix2<T> Adjoint(const Matrix2<T>& p_matrix);

        /**
		 * Return inverse matrix
		 */
		Matrix2<T> Inverse() const;
        
        /**
		 * Return inverse matrix
		 */
		static Matrix2<T> Inverse(const Matrix2<T>& p_matrix);

        #pragma endregion

    #pragma region Conversions
        /**
		 * Format matrix in readable string
		 */
		std::string ToString() const;

		/**
		 * Format matrix in readable string
		 * @param p_matrix
		 */
		static std::string ToString(const Matrix2<T>& p_matrix);


        /**
		 * Returns a 1-Dimensional array
		 */
		T* ToArray();

		/**
		 * Returns a 1-Dimensional array
		 * @param p_matrix
		 */
		static T* ToArray(const Matrix2<T>& p_matrix);

        /**
		 * Get row
		 * @param p_row
		 */
		Vector2<T> GetRow(uint8_t p_row);

        /**
		 * Get Column
		 * @param p_column
		 */
		Vector2<T> GetColumn(uint8_t p_column);

        #pragma endregion
	};

    /**
     * Output formatted matrix to stream
	 * @param p_stream
	 * @param p_matrix
	 */
	template<typename T>
	std::ostream& operator<<(std::ostream& p_stream, const Matrix2<T>& p_matrix);

    using Matrix2F = AltMath::Matrix2<float>;
	using Matrix2f = AltMath::Matrix2<float>;
	using Matrix2I = AltMath::Matrix2<int>;
	using Matrix2i = AltMath::Matrix2<int>;
}

#include "Matrix2.inl"

#endif //_MATRIX2_H

