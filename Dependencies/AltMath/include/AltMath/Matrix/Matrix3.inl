#pragma once

#ifndef _MATRIX3_INL
#define _MATRIX3_INL

#include <utility>
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include "Matrix2.h"
#include "AltMath/Vector/Vector2.h"
#include "AltMath/Vector/Vector3.h"
#include "AltMath/Tools/Utils.h"

namespace AltMath
{
	template <typename T>
	const Matrix3<T> Matrix3<T>::Zero = Matrix3<T>();

	template <typename T>
	const Matrix3<T> Matrix3<T>::Identity = Matrix3<T>(1.0f, 0.0f, 0.0f,
	                                                   0.0f, 1.0f, 0.0f,
	                                                   0.0f, 0.0f, 1.0f);

#pragma region Constructor & Assignement

	template <typename T>
	constexpr Matrix3<T>::Matrix3()
	{
		std::memset(elements, 0, 9 * sizeof(T));
	}

	template <typename T>
	constexpr Matrix3<T>::Matrix3(T p_value)
	{
		for (T& element : elements)
			element = p_value;
	}

	template <typename T>
	constexpr Matrix3<T>::Matrix3(T p_element1, T p_element2, T p_element3, T p_element4, T p_element5, T p_element6,
	                              T p_element7,
	                              T p_element8, T p_element9)
	{
		elements[0] = p_element1;
		elements[1] = p_element2;
		elements[2] = p_element3;
		elements[3] = p_element4;
		elements[4] = p_element5;
		elements[5] = p_element6;
		elements[6] = p_element7;
		elements[7] = p_element8;
		elements[8] = p_element9;
	}

	template <typename T>
	constexpr Matrix3<T>::Matrix3(const Matrix3<T>& p_other)
	{
		*this = p_other;
	}

	template <typename T>
	Matrix3<T>::Matrix3(Matrix3<T>&& p_other) noexcept
	{
		memmove(elements, p_other.elements, sizeof(T) * 9);
	}

	template <typename T>
	constexpr Matrix3<T>::Matrix3(const Matrix2<T>& p_matrix2)
	{
		elements[0] = p_matrix2.elements[0];
		elements[1] = p_matrix2.elements[1];
		elements[2] = 0;
		elements[3] = p_matrix2.elements[2];
		elements[4] = p_matrix2.elements[3];
		elements[5] = 0;
		elements[6] = 0;
		elements[7] = 0;
		elements[8] = 1;
	}

	template <typename T>
	Matrix3<T>& Matrix3<T>::operator=(const Matrix3<T>& p_other)
	{
		memcpy(this->elements, p_other.elements, 9 * sizeof(T));
		return *this;
	}

	template <typename T>
	Matrix3<T>& Matrix3<T>::operator=(Matrix3<T>&& p_other) noexcept
	{
		memmove(this->elements, p_other.elements, 9 * sizeof(T));
		return *this;
	}
#pragma endregion

#pragma region Tests & Comparisons

	template <typename T>
	constexpr bool Matrix3<T>::IsIdentity()
	{
		return memcmp(Identity.elements, elements, 9 * sizeof(T)) == 0;
	}

	template <typename T>
	constexpr bool Matrix3<T>::IsEqualTo(const Matrix3<T>& p_other)
	{
		return memcmp(this, p_other, 9 * sizeof(T)) == 0;
	}

	template <typename T>
	constexpr bool Matrix3<T>::AreEquals(const Matrix3<T>& p_left, const Matrix3<T>& p_right)
	{
		return memcmp(p_left, p_right, 9 * sizeof(T)) == 0;
	}

	template <typename T>
	constexpr bool Matrix3<T>::operator==(const Matrix3<T>& p_other)
	{
		return this->IsEqualTo(p_other);
	}

#pragma endregion

#pragma region Arithmetic Operations
#pragma region Addition

	template <typename T>
	Matrix3<T>& Matrix3<T>::Add(T p_scalar)
	{
		for (T& element : elements)
		{
			element += p_scalar;
		}
		return *this;
	}

	template <typename T>
	Matrix3<T> Matrix3<T>::Add(const Matrix3<T>& p_left, T p_scalar)
	{
		Matrix3<T> result(p_left);
		for (uint8_t i = 0; i < 9; ++i)
			result.elements[i] += p_scalar;
		return result;
	}

	template <typename T>
	Matrix3<T>& Matrix3<T>::Add(const Matrix3<T>& p_other)
	{
		for (uint8_t i = 0; i < 9; ++i)
			elements[i] += p_other.elements[i];

		return *this;
	}

	template <typename T>
	constexpr Matrix3<T> Matrix3<T>::Add(const Matrix3<T>& p_left, const Matrix3<T>& p_right)
	{
		Matrix3<T> result(p_left);
		for (uint8_t i = 0; i < 9; ++i)
			result.elements[i] += p_right.elements[i];
		return result;
	}

	template <typename T>
	constexpr Matrix3<T> Matrix3<T>::operator+(const Matrix3<T>& p_other) const
	{
		return Matrix3<T>::Add(*this, p_other);
	}

	template <typename T>
	Matrix3<T>& Matrix3<T>::operator+=(const Matrix3<T>& p_other)
	{
		return this->Add(p_other);
	}
#pragma endregion

#pragma region Subtraction

	template <typename T>
	Matrix3<T>& Matrix3<T>::Subtract(T p_scalar)
	{
		for (T& element : elements)
		{
			element -= p_scalar;
		}
		return *this;
	}

	template <typename T>
	constexpr Matrix3<T> Matrix3<T>::Subtract(const Matrix3<T>& p_left, T p_scalar)
	{
		Matrix3<T> result(p_left);
		for (T& element : result.elements)
		{
			element -= p_scalar;
		}
		return result;
	}

	template <typename T>
	Matrix3<T>& Matrix3<T>::Subtract(const Matrix3<T>& p_other)
	{
		for (uint8_t i = 0; i < 9; ++i)
			elements[i] -= p_other.elements[i];

		return *this;
	}

	template <typename T>
	constexpr Matrix3<T> Matrix3<T>::Subtract(const Matrix3<T>& p_left, const Matrix3<T>& p_right)
	{
		Matrix3<T> result(p_left);
		for (uint8_t i = 0; i < 9; ++i)
			result.elements[i] -= p_right.elements[i];
		return result;
	}

	template <typename T>
	constexpr Matrix3<T> Matrix3<T>::operator-(const Matrix3<T>& p_other) const
	{
		return Matrix3<T>::Subtract(*this, p_other);
	}

	template <typename T>
	Matrix3<T>& Matrix3<T>::operator-=(const Matrix3<T>& p_other)
	{
		return this->Subtract(p_other);
	}
#pragma endregion

#pragma region Scalar Product

	template <typename T>
	Matrix3<T>& Matrix3<T>::Multiply(T p_scalar)
	{
		for (T& element : elements)
			element *= p_scalar;
		return *this;
	}

	template <typename T>
	constexpr Matrix3<T> Matrix3<T>::Multiply(const Matrix3<T>& p_left, T p_scalar)
	{
		Matrix3<T> result(p_left);
		for (T& element : result.elements)
		{
			element *= p_scalar;
		}
		return result;
	}

	template <typename T>
	constexpr Matrix3<T> Matrix3<T>::operator*(T p_scalar) const
	{
		return Matrix3<T>::Multiply(*this, p_scalar);
	}

	template <typename T>
	Matrix3<T>& Matrix3<T>::operator*=(T p_scalar)
	{
		return this->Multiply(p_scalar);
	}
#pragma endregion

#pragma region Vector Product

	template <typename T>
	constexpr Vector3<T> Matrix3<T>::Multiply(const Vector3<T>& p_vector) const
	{
		Vector3<T> result;
		result.x = ((this->elements[0] * p_vector.x) + (this->elements[1] * p_vector.y) + (this->elements[2] * p_vector.
			z));
		result.y = ((this->elements[3] * p_vector.x) + (this->elements[4] * p_vector.y) + (this->elements[5] * p_vector.
			z));
		result.z = ((this->elements[6] * p_vector.x) + (this->elements[7] * p_vector.y) + (this->elements[8] * p_vector.
			z));

		return result;
	}

	template <typename T>
	constexpr Vector3<T> Matrix3<T>::Multiply(const Matrix3<T>& p_matrix, const Vector3<T>& p_vector)
	{
		Vector3<T> result;
		result.x = ((p_matrix.elements[0] * p_vector.x) + (p_matrix.elements[1] * p_vector.y) + (p_matrix.elements[2] *
			p_vector.z));
		result.y = ((p_matrix.elements[3] * p_vector.x) + (p_matrix.elements[4] * p_vector.y) + (p_matrix.elements[5] *
			p_vector.z));
		result.z = ((p_matrix.elements[6] * p_vector.x) + (p_matrix.elements[7] * p_vector.y) + (p_matrix.elements[8] *
			p_vector.z));

		return result;
	}

	template <typename T>
	constexpr Vector3<T> Matrix3<T>::operator*(const Vector3<T>& p_vector) const
	{
		return Matrix3<T>::Multiply(*this, p_vector);
	}

#pragma endregion

#pragma region Matrix Product

	template <typename T>
	Matrix3<T>& Matrix3<T>::Multiply(const Matrix3<T>& p_other)
	{
		Matrix3<T> previous(*this);

		this->elements[0] = (previous.elements[0] * p_other.elements[0] + previous.elements[1] * p_other.elements[3] +
			previous.elements[2] * p_other.elements[6]);
		this->elements[1] = (previous.elements[0] * p_other.elements[1] + previous.elements[1] * p_other.elements[4] +
			previous.elements[2] * p_other.elements[7]);
		this->elements[2] = (previous.elements[0] * p_other.elements[2] + previous.elements[1] * p_other.elements[5] +
			previous.elements[2] * p_other.elements[8]);

		this->elements[3] = (previous.elements[3] * p_other.elements[0] + previous.elements[4] * p_other.elements[3] +
			previous.elements[5] * p_other.elements[6]);
		this->elements[4] = (previous.elements[3] * p_other.elements[1] + previous.elements[4] * p_other.elements[4] +
			previous.elements[5] * p_other.elements[7]);
		this->elements[5] = (previous.elements[3] * p_other.elements[2] + previous.elements[4] * p_other.elements[5] +
			previous.elements[5] * p_other.elements[8]);

		this->elements[6] = (previous.elements[6] * p_other.elements[0] + previous.elements[7] * p_other.elements[3] +
			previous.elements[8] * p_other.elements[6]);
		this->elements[7] = (previous.elements[6] * p_other.elements[1] + previous.elements[7] * p_other.elements[4] +
			previous.elements[8] * p_other.elements[7]);
		this->elements[8] = (previous.elements[6] * p_other.elements[2] + previous.elements[7] * p_other.elements[5] +
			previous.elements[8] * p_other.elements[8]);

		return *this;
	}

	template <typename T>
	constexpr Matrix3<T> Matrix3<T>::Multiply(const Matrix3<T>& p_left, const Matrix3<T>& p_right)
	{
		return Matrix3<T>(
			(p_left.elements[0] * p_right.elements[0]) + (p_left.elements[1] * p_right.elements[3]) + (p_left.elements[2
			] * p_right.elements[6]),
			(p_left.elements[0] * p_right.elements[1]) + (p_left.elements[1] * p_right.elements[4]) + (p_left.elements[2
			] * p_right.elements[7]),
			(p_left.elements[0] * p_right.elements[2]) + (p_left.elements[1] * p_right.elements[5]) + (p_left.elements[2
			] * p_right.elements[8]),

			(p_left.elements[3] * p_right.elements[0]) + (p_left.elements[4] * p_right.elements[3]) + (p_left.elements[5
			] * p_right.elements[6]),
			(p_left.elements[3] * p_right.elements[1]) + (p_left.elements[4] * p_right.elements[4]) + (p_left.elements[5
			] * p_right.elements[7]),
			(p_left.elements[3] * p_right.elements[2]) + (p_left.elements[4] * p_right.elements[5]) + (p_left.elements[5
			] * p_right.elements[8]),

			(p_left.elements[6] * p_right.elements[0]) + (p_left.elements[7] * p_right.elements[3]) + (p_left.elements[8
			] * p_right.elements[6]),
			(p_left.elements[6] * p_right.elements[1]) + (p_left.elements[7] * p_right.elements[4]) + (p_left.elements[8
			] * p_right.elements[7]),
			(p_left.elements[6] * p_right.elements[2]) + (p_left.elements[7] * p_right.elements[5]) + (p_left.elements[8
			] * p_right.elements[8]));
	}

	template <typename T>
	constexpr Matrix3<T> Matrix3<T>::operator*(const Matrix3<T>& p_other) const
	{
		return Matrix3<T>::Multiply(*this, p_other);
	}

	template <typename T>
	Matrix3<T>& Matrix3<T>::operator*=(const Matrix3<T>& p_other)
	{
		return this->Multiply(p_other);
	}

#pragma endregion

#pragma region Scalar Division

	template <typename T>
	constexpr Matrix3<T>& Matrix3<T>::Divide(T p_scalar)
	{
		for (T& element : elements)
			element /= p_scalar;
		return *this;
	}

	template <typename T>
	constexpr Matrix3<T> Matrix3<T>::Divide(const Matrix3<T>& p_left, T p_scalar)
	{
		Matrix3<T> result(p_left);
		for (T& element : result.elements)
		{
			element /= p_scalar;
		}
		return result;
	}

	template <typename T>
	constexpr Matrix3<T> Matrix3<T>::operator/(T p_scalar) const
	{
		return Matrix3<T>::Divide(*this, p_scalar);
	}

	template <typename T>
	Matrix3<T>& Matrix3<T>::operator/=(T p_scalar)
	{
		return this->Divide(p_scalar);
	}

#pragma endregion

#pragma region Matrix Division

	template <typename T>
	Matrix3<T>& Matrix3<T>::Divide(const Matrix3<T>& p_other)
	{
		return *this *= p_other.Inverse();
	}

	template <typename T>
	constexpr Matrix3<T> Matrix3<T>::Divide(const Matrix3<T>& p_left, const Matrix3<T>& p_right)
	{
		return (p_left * p_right.Inverse());
	}

	template <typename T>
	constexpr Matrix3<T> Matrix3<T>::operator/(const Matrix3<T>& p_other) const
	{
		return Matrix3<T>::Divide(*this, p_other);
	}

	template <typename T>
	Matrix3<T>& Matrix3<T>::operator/=(const Matrix3<T>& p_other)
	{
		return this->Divide(p_other);
	}

#pragma endregion
#pragma endregion

#pragma region Matrix Operations

	template <typename T>
	constexpr T Matrix3<T>::Determinant() const
	{
		return (elements[0] * ((elements[4] * elements[8]) - (elements[5] * elements[7])) -
			elements[1] * ((elements[3] * elements[8]) - (elements[5] * elements[5])) +
			elements[2] * ((elements[3] * elements[7]) - (elements[4] * elements[6])));
	}

	template <typename T>
	constexpr T Matrix3<T>::Determinant(const Matrix3<T>& p_matrix)
	{
		return (p_matrix.elements[0] * ((p_matrix.elements[4] * p_matrix.elements[8]) - (p_matrix.elements[5] * p_matrix
				.elements[7])) -
			p_matrix.elements[1] * ((p_matrix.elements[3] * p_matrix.elements[8]) - (p_matrix.elements[5] * p_matrix.
				elements[5])) +
			p_matrix.elements[2] * ((p_matrix.elements[3] * p_matrix.elements[7]) - (p_matrix.elements[4] * p_matrix.
				elements[6])));
	}

	template <typename T>
	Matrix3<T>& Matrix3<T>::Transpose()
	{
		Matrix3<T> previous(*this);

		elements[1] = previous.elements[3];
		elements[2] = previous.elements[6];
		elements[3] = previous.elements[1];

		elements[5] = previous.elements[7];
		elements[6] = previous.elements[2];
		elements[7] = previous.elements[5];

		return *this;
	}

	template <typename T>
	constexpr Matrix3<T> Matrix3<T>::Transpose(const Matrix3<T>& p_matrix)
	{
		return Matrix3<T>(p_matrix).Transpose();
	}

	template <typename T>
	constexpr Matrix3<T> Matrix3<T>::Cofactor() const
	{
		return Matrix3<T>(((elements[4] * elements[8]) - (elements[5] * elements[7])), //0
		                  -((elements[3] * elements[8]) - (elements[5] * elements[6])), //1
		                  ((elements[3] * elements[7]) - (elements[4] * elements[6])), //2
		                  -((elements[1] * elements[8]) - (elements[2] * elements[7])), //3
		                  ((elements[0] * elements[8]) - (elements[2] * elements[6])), //4
		                  -((elements[0] * elements[7]) - (elements[1] * elements[6])), //5
		                  ((elements[1] * elements[5]) - (elements[2] * elements[4])), //6
		                  -((elements[0] * elements[5]) - (elements[2] * elements[3])), //7 
		                  ((elements[0] * elements[4]) - (elements[1] * elements[3]))); //8
	}

	template <typename T>
	constexpr Matrix3<T> Matrix3<T>::Cofactor(const Matrix3<T>& p_matrix)
	{
		return Matrix3<T>(
			((p_matrix.elements[4] * p_matrix.elements[8]) - (p_matrix.elements[5] * p_matrix.elements[7])), //0
			-((p_matrix.elements[3] * p_matrix.elements[8]) - (p_matrix.elements[5] * p_matrix.elements[6])), //1
			((p_matrix.elements[3] * p_matrix.elements[7]) - (p_matrix.elements[4] * p_matrix.elements[6])), //2
			-((p_matrix.elements[1] * p_matrix.elements[8]) - (p_matrix.elements[2] * p_matrix.elements[7])), //3
			((p_matrix.elements[0] * p_matrix.elements[8]) - (p_matrix.elements[2] * p_matrix.elements[6])), //4
			-((p_matrix.elements[0] * p_matrix.elements[7]) - (p_matrix.elements[1] * p_matrix.elements[6])), //5
			((p_matrix.elements[1] * p_matrix.elements[5]) - (p_matrix.elements[2] * p_matrix.elements[4])), //6
			-((p_matrix.elements[0] * p_matrix.elements[5]) - (p_matrix.elements[2] * p_matrix.elements[3])), //7 
			((p_matrix.elements[0] * p_matrix.elements[4]) - (p_matrix.elements[1] * p_matrix.elements[3]))); //8
	}

	template <typename T>
	constexpr Matrix3<T> Matrix3<T>::Minor() const
	{
		return Matrix3<T>(((elements[4] * elements[8]) - (elements[5] * elements[7])), //0
		                  ((elements[3] * elements[8]) - (elements[5] * elements[6])), //1
		                  ((elements[3] * elements[7]) - (elements[4] * elements[6])), //2
		                  ((elements[1] * elements[8]) - (elements[2] * elements[7])), //3
		                  ((elements[0] * elements[8]) - (elements[2] * elements[6])), //4
		                  ((elements[0] * elements[7]) - (elements[1] * elements[6])), //5
		                  ((elements[1] * elements[5]) - (elements[2] * elements[4])), //6
		                  ((elements[0] * elements[5]) - (elements[2] * elements[3])), //7 
		                  ((elements[0] * elements[4]) - (elements[1] * elements[3]))); //8
	}

	template <typename T>
	constexpr Matrix3<T> Matrix3<T>::Minor(const Matrix3<T>& p_matrix)
	{
		return Matrix3<T>(
			((p_matrix.elements[4] * p_matrix.elements[8]) - (p_matrix.elements[5] * p_matrix.elements[7])), //0
			((p_matrix.elements[3] * p_matrix.elements[8]) - (p_matrix.elements[5] * p_matrix.elements[6])), //1
			((p_matrix.elements[3] * p_matrix.elements[7]) - (p_matrix.elements[4] * p_matrix.elements[6])), //2
			((p_matrix.elements[1] * p_matrix.elements[8]) - (p_matrix.elements[2] * p_matrix.elements[7])), //3
			((p_matrix.elements[0] * p_matrix.elements[8]) - (p_matrix.elements[2] * p_matrix.elements[6])), //4
			((p_matrix.elements[0] * p_matrix.elements[7]) - (p_matrix.elements[1] * p_matrix.elements[6])), //5
			((p_matrix.elements[1] * p_matrix.elements[5]) - (p_matrix.elements[2] * p_matrix.elements[4])), //6
			((p_matrix.elements[0] * p_matrix.elements[5]) - (p_matrix.elements[2] * p_matrix.elements[3])), //7 
			((p_matrix.elements[0] * p_matrix.elements[4]) - (p_matrix.elements[1] * p_matrix.elements[3]))); //8
	}

	template <typename T>
	constexpr Matrix3<T> Matrix3<T>::Adjoint() const
	{
		return Cofactor().Transpose();
	}

	template <typename T>
	constexpr Matrix3<T> Matrix3<T>::Adjoint(const Matrix3<T>& p_other)
	{
		return p_other.Cofactor().Transpose();
	}

	template <typename T>
	constexpr Matrix3<T> Matrix3<T>::Inverse() const
	{
		T determinant = this->Determinant();
		if (determinant == 0)
			throw std::logic_error("Division by 0");

		return this->Adjoint() / determinant;
	}

	template <typename T>
	constexpr Matrix3<T> Matrix3<T>::Inverse(const Matrix3<T>& p_matrix)
	{
		T determinant = p_matrix->Determinant();
		if (determinant == 0)
			throw std::logic_error("Division by 0");

		return p_matrix.Adjoint() / determinant;
	}

	template <typename T>
	constexpr Matrix3<T> Matrix3<T>::Translation(const Vector2<T>& p_translation)
	{
		return Matrix3<T>(1, 0, p_translation.x,
		                  0, 1, p_translation.y,
		                  0, 0, 1);
	}

	template <typename T>
	constexpr Matrix3<T> Matrix3<T>::Translate(const Matrix3<T>& p_matrix, const Vector2<T>& p_translation)
	{
		return p_matrix * Matrix3<T>::Translation(p_translation);
	}

	template <typename T>
	Matrix3<T>& Matrix3<T>::Translate(const Vector2<T>& p_translation)
	{
		return *this *= Matrix3<T>::Translation(p_translation);
	}

	template <typename T>
	constexpr Matrix3<T> Matrix3<T>::Rotation(float p_rotation)
	{
		return Matrix3<T>(Tools::Utils::Cos(p_rotation), -Tools::Utils::Sin(p_rotation), 0,
		                  Tools::Utils::Sin(p_rotation), Tools::Utils::Cos(p_rotation), 0,
		                  0, 0, 1);
	}

	template <typename T>
	constexpr Matrix3<T> Matrix3<T>::Rotate(const Matrix3<T>& p_matrix, float p_rotation)
	{
		return p_matrix * Matrix3<T>::Rotation(p_rotation);
	}

	template <typename T>
	Matrix3<T>& Matrix3<T>::Rotate(float p_rotation)
	{
		return *this *= Matrix3<T>::Rotation(p_rotation);
	}

	template <typename T>
	constexpr Matrix3<T> Matrix3<T>::Scaling(const Vector2<T>& p_scale)
	{
		return Matrix3<T>(p_scale.x, 0, 0,
		                  0, p_scale.y, 0,
		                  0, 0, 1);
	}

	template <typename T>
	constexpr Matrix3<T> Matrix3<T>::Scale(const Matrix3<T>& p_matrix, const Vector2<T>& p_scale)
	{
		return p_matrix * Matrix3<T>::Scaling(p_scale);
	}

	template <typename T>
	Matrix3<T>& Matrix3<T>::Scale(const Vector2<T>& p_scale)
	{
		return *this *= Matrix3<T>::Scaling(p_scale);
	}
#pragma endregion

#pragma region Conversions & Accessors

	template <typename T>
	T& Matrix3<T>::operator()(const uint8_t p_row, const uint8_t p_column)
	{
		if (p_row >= 3 || p_column >= 3)
			throw std::out_of_range(
				"Invalid index : " + std::to_string(p_row) + "," + std::to_string(p_column) + " is out of range");
		return elements[3 * p_row + p_column];
	}

	template <typename T>
	constexpr Vector3<T> Matrix3<T>::GetRow(const uint8_t p_row) const
	{
		if (p_row >= 3)
			throw std::out_of_range("Invalid index : " + std::to_string(p_row) + " is out of range");

		return Vector3<T>(p_row * 3, p_row * 3 + 1, p_row * 3 + 2);
	}

	template <typename T>
	constexpr Vector3<T> Matrix3<T>::GetColumn(uint8_t p_column) const
	{
		if (p_column >= 3)
			throw std::out_of_range("Invalid index : " + std::to_string(p_column) + " is out of range");

		return Vector3<T>(elements[p_column], elements[p_column + 3], elements[p_column + 6]);
	}

	template <typename T>
	constexpr T* Matrix3<T>::ToArray()
	{
		return elements;
	}

	template <typename T>
	constexpr T* Matrix3<T>::ToArray(const Matrix3<T>& p_matrix)
	{
		return p_matrix.elements;
	}

	template <typename T>
	std::string Matrix3<T>::ToString()
	{
		std::stringstream ss;
		ss << elements[0] << "\t" << elements[1] << "\t" << elements[2] << "\n" <<
			elements[3] << "\t" << elements[4] << "\t" << elements[5] << "\n" <<
			elements[6] << "\t" << elements[7] << "\t" << elements[8] << "\t";
		std::string result = ss.str();
		return result;
	}

	template <typename T>
	std::string Matrix3<T>::ToString(const Matrix3<T>& p_matrix)
	{
		std::stringstream ss;
		ss << p_matrix.elements[0] << "\t" << p_matrix.elements[1] << "\t" << p_matrix.elements[2] << "\n" <<
			p_matrix.elements[3] << "\t" << p_matrix.elements[4] << "\t" << p_matrix.elements[5] << "\n" <<
			p_matrix.elements[6] << "\t" << p_matrix.elements[7] << "\t" << p_matrix.elements[8] << "\t";
		std::string result = ss.str();
		return result;
	}

	template <typename T>
	std::ostream& operator<<(std::ostream& p_stream, const Matrix3<T>& p_matrix)
	{
		p_stream << p_matrix.elements[0] << "\t" << p_matrix.elements[1] << "\t" << p_matrix.elements[2] << "\n" <<
			p_matrix.elements[3] << "\t" << p_matrix.elements[4] << "\t" << p_matrix.elements[5] << "\n" <<
			p_matrix.elements[6] << "\t" << p_matrix.elements[7] << "\t" << p_matrix.elements[8] << "\t";
		return p_stream;
	}
#pragma endregion
}
#endif // ! _MATRIX3_INL
