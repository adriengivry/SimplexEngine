#pragma once

#ifndef _MATRIX4_INL
#define _MATRIX4_INL
#define _USE_MATH_DEFINES
#include <cmath>
#include <utility>
#include <string>
#include <sstream>
#include <iostream>
#include "Matrix4.h"

namespace AltMath
{
	template <typename T>
	const Matrix4<T> Matrix4<T>::Identity = Matrix4<T>(1.f, 0.f, 0.f, 0.f,
	                                                   0.f, 1.f, 0.f, 0.f,
	                                                   0.f, 0.f, 1.f, 0.f,
	                                                   0.f, 0.f, 0.f, 1.f);

#pragma region Constructor & Assignement

	template <typename T>
	Matrix4<T>::Matrix4()
	{
		memcpy(this->elements, Matrix4<T>::Identity.elements, 16 * sizeof(T));
	}

	template <typename T>
	Matrix4<T>::Matrix4(T p_element1, T p_element2, T p_element3, T p_element4,
	                    T p_element5, T p_element6, T p_element7, T p_element8,
	                    T p_element9, T p_element10, T p_element11, T p_element12,
	                    T p_element13, T p_element14, T p_element15, T p_element16)
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
		elements[9] = p_element10;
		elements[10] = p_element11;
		elements[11] = p_element12;
		elements[12] = p_element13;
		elements[13] = p_element14;
		elements[14] = p_element15;
		elements[15] = p_element16;
	}

	template <typename T>
	Matrix4<T>::Matrix4(Matrix4<T>&& p_other)
	{
		memmove(this->elements, p_other.elements, 16 * sizeof(T));
	}

	template <typename T>
	Matrix4<T>::Matrix4(const Matrix4<T>& p_other)
	{
		*this = p_other;
	}

	template <typename T>
	Matrix4<T> Matrix4<T>::operator=(Matrix4<T>&& p_other)
	{
		memcpy(this->elements, p_other.elements, 16 * sizeof(T));
		return *this;
	}

	template <typename T>
	Matrix4<T>& Matrix4<T>::operator=(const Matrix4<T>& p_other)
	{
		memmove(this->elements, p_other.elements, 16 * sizeof(T));
		return *this;
	}
#pragma endregion

#pragma region Arithmetic Operation

	template <typename T>
	Matrix4<T>& Matrix4<T>::Add(const Matrix4<T>& p_other)
	{
		for (int8_t i = 0; i < 16; i++)
			this->elements[i] += p_other.elements[i];
		return *this;
	}

	template <typename T>
	Matrix4<T> Matrix4<T>::Add(const Matrix4<T>& p_left, const Matrix4<T>& p_right)
	{
		Matrix4<T> result(p_left);
		for (int8_t i = 0; i < 16; i++)
			result.elements[i] += p_right.elements[i];
		return result;
	}

	template <typename T>
	Matrix4<T> Matrix4<T>::operator+(const Matrix4<T>& p_other) const
	{
		return Add(*this, p_other);
	}

	template <typename T>
	Matrix4<T>& Matrix4<T>::operator+=(const Matrix4<T>& p_other)
	{
		return this->Add(p_other);
	}

	template <typename T>
	Matrix4<T>& Matrix4<T>::Subtract(const Matrix4<T>& p_other)
	{
		for (int8_t i = 0; i < 16; ++i)
			this->elements[i] -= p_other.elements[i];
		return *this;
	}

	template <typename T>
	Matrix4<T> Matrix4<T>::Subtract(const Matrix4<T>& p_left, const Matrix4<T>& p_right)
	{
		Matrix4<T> result(p_left);
		for (int8_t i = 0; i < 16; ++i)
			result.elements[i] -= p_right.elements[i];
		return result;
	}

	template <typename T>
	Matrix4<T> Matrix4<T>::operator-(const Matrix4<T>& p_other) const
	{
		return Subtract(*this, p_other);
	}

	template <typename T>
	Matrix4<T>& Matrix4<T>::operator-=(const Matrix4<T>& p_other)
	{
		return this->Subtract(p_other);
	}

	template <typename T>
	Matrix4<T>& Matrix4<T>::Multiply(T p_scalar)
	{
		for (T& element : elements)
			element *= p_scalar;
		return *this;
	}

	template <typename T>
	Matrix4<T> Matrix4<T>::Multiply(const Matrix4<T>& p_left, T p_scalar)
	{
		Matrix4<T> result(p_left);
		for (T& element : result.elements)
			element *= p_scalar;
		return result;
	}

	template <typename T>
	Matrix4<T> Matrix4<T>::operator*(T p_scalar) const
	{
		return Multiply(*this, p_scalar);
	}

	template <typename T>
	Matrix4<T>& Matrix4<T>::operator*=(T p_scalar)
	{
		return this->Multiply(p_scalar);
	}

	template <typename T>
	Vector4<T> Matrix4<T>::Multiply(const Vector4<T>& p_vector) const
	{
		Vector4<T> multiply;

		multiply.x = ((this->elements[0] * p_vector.x) + (this->elements[1] * p_vector.y) + (this->elements[2] *
			p_vector.z) + (this->elements[3] * p_vector.w));
		multiply.y = ((this->elements[4] * p_vector.x) + (this->elements[5] * p_vector.y) + (this->elements[6] *
			p_vector.z) + (this->elements[7] * p_vector.w));
		multiply.z = ((this->elements[8] * p_vector.x) + (this->elements[9] * p_vector.y) + (this->elements[10] *
			p_vector.z) + (this->elements[11] * p_vector.w));
		multiply.w = ((this->elements[12] * p_vector.x) + (this->elements[13] * p_vector.y) + (this->elements[14] *
			p_vector.z) + (this->elements[15] * p_vector.w));
		return multiply;
	}

	template <typename T>
	Vector4<T> Matrix4<T>::Multiply(const Matrix4<T>& p_matrix, const Vector4<T>& p_vector)
	{
		Vector4<T> multiply;

		multiply.x = ((p_matrix.elements[0] * p_vector.x) + (p_matrix.elements[1] * p_vector.y) + (p_matrix.elements[2]
			* p_vector.z) + (p_matrix.elements[3] * p_vector.w));
		multiply.y = ((p_matrix.elements[4] * p_vector.x) + (p_matrix.elements[5] * p_vector.y) + (p_matrix.elements[6]
			* p_vector.z) + (p_matrix.elements[7] * p_vector.w));
		multiply.z = ((p_matrix.elements[8] * p_vector.x) + (p_matrix.elements[9] * p_vector.y) + (p_matrix.elements[10]
			* p_vector.z) + (p_matrix.elements[11] * p_vector.w));
		multiply.w = ((p_matrix.elements[12] * p_vector.x) + (p_matrix.elements[13] * p_vector.y) + (p_matrix.elements[
			14] * p_vector.z) + (p_matrix.elements[15] * p_vector.w));
		return multiply;
	}

	template <typename T>
	Vector4<T>& Matrix4<T>::operator*=(const Vector4<T>& p_vector)
	{
		this = Multiply(p_vector);
		return *this;
	}

	template <typename T>
	Vector4<T> Matrix4<T>::operator*(const Vector4<T>& p_vector)
	{
		return Multiply(*this, p_vector);
	}

	template <typename T>
	Matrix4<T>& Matrix4<T>::Multiply(const Matrix4<T>& p_other)
	{
		Matrix4<T> previous(*this);

		this->elements[0] = ((previous.elements[0] * p_other.elements[0]) + (previous.elements[1] * p_other.elements[4])
			+ (previous.elements[2] * p_other.elements[8]) + (previous.elements[3] * p_other.elements[12]));
		this->elements[1] = ((previous.elements[0] * p_other.elements[1]) + (previous.elements[1] * p_other.elements[5])
			+ (previous.elements[2] * p_other.elements[9]) + (previous.elements[3] * p_other.elements[13]));
		this->elements[2] = ((previous.elements[0] * p_other.elements[2]) + (previous.elements[1] * p_other.elements[6])
			+ (previous.elements[2] * p_other.elements[10]) + (previous.elements[3] * p_other.elements[14]));
		this->elements[3] = ((previous.elements[0] * p_other.elements[3]) + (previous.elements[1] * p_other.elements[7])
			+ (previous.elements[2] * p_other.elements[11]) + (previous.elements[3] * p_other.elements[15]));

		this->elements[4] = ((previous.elements[4] * p_other.elements[0]) + (previous.elements[5] * p_other.elements[4])
			+ (previous.elements[6] * p_other.elements[8]) + (previous.elements[7] * p_other.elements[12]));
		this->elements[5] = ((previous.elements[4] * p_other.elements[1]) + (previous.elements[5] * p_other.elements[5])
			+ (previous.elements[6] * p_other.elements[9]) + (previous.elements[7] * p_other.elements[13]));
		this->elements[6] = ((previous.elements[4] * p_other.elements[2]) + (previous.elements[5] * p_other.elements[6])
			+ (previous.elements[6] * p_other.elements[10]) + (previous.elements[7] * p_other.elements[14]));
		this->elements[7] = ((previous.elements[4] * p_other.elements[3]) + (previous.elements[5] * p_other.elements[7])
			+ (previous.elements[6] * p_other.elements[11]) + (previous.elements[7] * p_other.elements[15]));

		this->elements[8] = ((previous.elements[8] * p_other.elements[0]) + (previous.elements[9] * p_other.elements[4])
			+ (previous.elements[10] * p_other.elements[8]) + (previous.elements[11] * p_other.elements[12]));
		this->elements[9] = ((previous.elements[8] * p_other.elements[1]) + (previous.elements[9] * p_other.elements[5])
			+ (previous.elements[10] * p_other.elements[9]) + (previous.elements[11] * p_other.elements[13]));
		this->elements[10] = ((previous.elements[8] * p_other.elements[2]) + (previous.elements[9] * p_other.elements[6]
		) + (previous.elements[10] * p_other.elements[10]) + (previous.elements[11] * p_other.elements[14]));
		this->elements[11] = ((previous.elements[8] * p_other.elements[3]) + (previous.elements[9] * p_other.elements[7]
		) + (previous.elements[10] * p_other.elements[11]) + (previous.elements[11] * p_other.elements[15]));

		this->elements[12] = ((previous.elements[12] * p_other.elements[0]) + (previous.elements[13] * p_other.elements[
			4]) + (previous.elements[14] * p_other.elements[8]) + (previous.elements[15] * p_other.elements[12]));
		this->elements[13] = ((previous.elements[12] * p_other.elements[1]) + (previous.elements[13] * p_other.elements[
			5]) + (previous.elements[14] * p_other.elements[9]) + (previous.elements[15] * p_other.elements[13]));
		this->elements[14] = ((previous.elements[12] * p_other.elements[2]) + (previous.elements[13] * p_other.elements[
			6]) + (previous.elements[14] * p_other.elements[10]) + (previous.elements[15] * p_other.elements[14]));
		this->elements[15] = ((previous.elements[12] * p_other.elements[3]) + (previous.elements[13] * p_other.elements[
			7]) + (previous.elements[14] * p_other.elements[11]) + (previous.elements[15] * p_other.elements[15]));
		return *this;
	}

	template <typename T>
	Matrix4<T> Matrix4<T>::Multiply(const Matrix4<T>& p_left, const Matrix4<T>& p_right)
	{
		return Matrix4<T>(
			((p_left.elements[0] * p_right.elements[0]) + (p_left.elements[1] * p_right.elements[4]) + (p_left.elements[
				2] * p_right.elements[8]) + (p_left.elements[3] * p_right.elements[12])),
			((p_left.elements[0] * p_right.elements[1]) + (p_left.elements[1] * p_right.elements[5]) + (p_left.elements[
				2] * p_right.elements[9]) + (p_left.elements[3] * p_right.elements[13])),
			((p_left.elements[0] * p_right.elements[2]) + (p_left.elements[1] * p_right.elements[6]) + (p_left.elements[
				2] * p_right.elements[10]) + (p_left.elements[3] * p_right.elements[14])),
			((p_left.elements[0] * p_right.elements[3]) + (p_left.elements[1] * p_right.elements[7]) + (p_left.elements[
				2] * p_right.elements[11]) + (p_left.elements[3] * p_right.elements[15])),

			((p_left.elements[4] * p_right.elements[0]) + (p_left.elements[5] * p_right.elements[4]) + (p_left.elements[
				6] * p_right.elements[8]) + (p_left.elements[7] * p_right.elements[12])),
			((p_left.elements[4] * p_right.elements[1]) + (p_left.elements[5] * p_right.elements[5]) + (p_left.elements[
				6] * p_right.elements[9]) + (p_left.elements[7] * p_right.elements[13])),
			((p_left.elements[4] * p_right.elements[2]) + (p_left.elements[5] * p_right.elements[6]) + (p_left.elements[
				6] * p_right.elements[10]) + (p_left.elements[7] * p_right.elements[14])),
			((p_left.elements[4] * p_right.elements[3]) + (p_left.elements[5] * p_right.elements[7]) + (p_left.elements[
				6] * p_right.elements[11]) + (p_left.elements[7] * p_right.elements[15])),

			((p_left.elements[8] * p_right.elements[0]) + (p_left.elements[9] * p_right.elements[4]) + (p_left.elements[
				10] * p_right.elements[8]) + (p_left.elements[11] * p_right.elements[12])),
			((p_left.elements[8] * p_right.elements[1]) + (p_left.elements[9] * p_right.elements[5]) + (p_left.elements[
				10] * p_right.elements[9]) + (p_left.elements[11] * p_right.elements[13])),
			((p_left.elements[8] * p_right.elements[2]) + (p_left.elements[9] * p_right.elements[6]) + (p_left.elements[
				10] * p_right.elements[10]) + (p_left.elements[11] * p_right.elements[14])),
			((p_left.elements[8] * p_right.elements[3]) + (p_left.elements[9] * p_right.elements[7]) + (p_left.elements[
				10] * p_right.elements[11]) + (p_left.elements[11] * p_right.elements[15])),

			((p_left.elements[12] * p_right.elements[0]) + (p_left.elements[13] * p_right.elements[4]) + (p_left.
				elements[14] * p_right.elements[8]) + (p_left.elements[15] * p_right.elements[12])),
			((p_left.elements[12] * p_right.elements[1]) + (p_left.elements[13] * p_right.elements[5]) + (p_left.
				elements[14] * p_right.elements[9]) + (p_left.elements[15] * p_right.elements[13])),
			((p_left.elements[12] * p_right.elements[2]) + (p_left.elements[13] * p_right.elements[6]) + (p_left.
				elements[14] * p_right.elements[10]) + (p_left.elements[15] * p_right.elements[14])),
			((p_left.elements[12] * p_right.elements[3]) + (p_left.elements[13] * p_right.elements[7]) + (p_left.
				elements[14] * p_right.elements[11]) + (p_left.elements[15] * p_right.elements[15])));
	}

	template <typename T>
	Matrix4<T> Matrix4<T>::operator*(const Matrix4<T>& p_other) const
	{
		return Multiply(*this, p_other);
	}

	template <typename T>
	Matrix4<T>& Matrix4<T>::operator*=(const Matrix4<T>& p_other)
	{
		return this->Multiply(p_other);
	}

	template <typename T>
	Matrix4<T> Matrix4<T>::Divide(T p_scalar)
	{
		for (T& element : elements)
			element /= p_scalar;
		return *this;
	}

	template <typename T>
	Matrix4<T> Matrix4<T>::Divide(const Matrix4<T>& p_left, T p_scalar)
	{
		Matrix4<T> result(p_left);
		for (T& element : result.elements)
			element /= p_scalar;

		return result;
	}

	template <typename T>
	Matrix4<T> Matrix4<T>::operator/(T p_scalar) const
	{
		return Divide(*this, p_scalar);
	}

	template <typename T>
	Matrix4<T>& Matrix4<T>::operator/=(T p_scalar)
	{
		return this->Divide(p_scalar);
	}

	template <typename T>
	Matrix4<T> Matrix4<T>::Divide(const Matrix4<T>& p_other)
	{
		return *this *= p_other.Inverse();
	}

	template <typename T>
	Matrix4<T> Matrix4<T>::Divide(const Matrix4<T>& p_left, const Matrix4<T>& p_right)
	{
		Matrix4<T> leftCopy(p_left);
		return (leftCopy * p_right.Inverse());
	}

	template <typename T>
	Matrix4<T> Matrix4<T>::operator/(const Matrix4<T>& p_other) const
	{
		return Divide(*this, p_other);
	}

	template <typename T>
	Matrix4<T>& Matrix4<T>::operator/=(const Matrix4<T>& p_other)
	{
		return this->Divide(p_other);
	}

#pragma endregion

#pragma region Matrix Operation

	template <typename T>
	Matrix4<float> Matrix4<T>::CreateView(const float p_eyeX, const float p_eyeY, const float p_eyeZ,
	                                      const float p_lookX, const float p_lookY, const float p_lookZ,
	                                      const float p_upX, const float p_upY, const float p_upZ)
	{
		const Vector3<float> eye(p_eyeX, p_eyeY, p_eyeZ);
		const Vector3<float> look(p_lookX, p_lookY, p_lookZ);
		const Vector3<float> up(p_upX, p_upY, p_upZ);
		const Vector3<float> eye_look(eye - look);
		const Vector3<float> n(eye_look / eye_look.Length());
		const Vector3<float> UpXn(up.CrossProduct(n));
		const Vector3<float> u(UpXn / UpXn.Length());
		const Vector3<float> v(n.CrossProduct(u));
		Matrix4<float> View;
		View.elements[0] = u.x;
		View.elements[1] = u.y;
		View.elements[2] = u.z;
		View.elements[3] = -eye.DotProduct(u);
		View.elements[4] = v.x;
		View.elements[5] = v.y;
		View.elements[6] = v.z;
		View.elements[7] = -eye.DotProduct(v);
		View.elements[8] = n.x;
		View.elements[9] = n.y;
		View.elements[10] = n.z;
		View.elements[11] = -eye.DotProduct(n);
		return View;
	}

	template <typename T>
	Matrix4<float> Matrix4<T>::CreateFrustum(const float p_left, const float p_right, const float p_bottom,
	                                         const float p_top, const float p_zNear, const float p_zFar)
	{
		const float maxView = 2.0f * p_zNear;
		const float width = p_right - p_left;
		const float height = p_top - p_bottom;
		const float zRange = p_zFar - p_zNear;
		Matrix4<float> Frustum;
		Frustum.elements[0] = maxView / width;
		Frustum.elements[5] = maxView / height;
		Frustum.elements[8] = (p_right + p_left) / width;
		Frustum.elements[9] = (p_top + p_bottom) / height;
		Frustum.elements[10] = (-p_zFar - p_zNear) / zRange;
		Frustum.elements[11] = -1.0f;
		Frustum.elements[14] = (-maxView * p_zFar) / zRange;
		Frustum.elements[15] = 0.0f;
		return Frustum;
	}

	template <typename T>
	Matrix4<float> Matrix4<T>::CreatePerspective(const float p_fov, const float p_aspectRatio, const float p_zNear,
	                                             const float p_zFar)
	{
		const float tangent = tanf(p_fov / 2.0f * Tools::Generics::Pi / 180.0f);
		const float height = p_zNear * tangent;
		const float width = height * p_aspectRatio;
		return CreateFrustum(-width, width, -height, height, p_zNear, p_zFar);
	}

	template <typename T>
	bool Matrix4<T>::IsIdentity()
	{
		int8_t counter = 0;
		for (int8_t x = 0; x < 4; x++)
		{
			for (int8_t y = 0; y < 4; y++)
			{
				if (x == y)
				{
					elements[4 * x + y] == 1;
					counter++;
				}
				else
				{
					elements[4 * x + y] == 0;
					counter++;
				}
			}
		}
		if (counter == 16)
			return true;
		else
			return false;
	}

	template <typename T>
	inline constexpr Matrix4<T> Matrix4<T>::Translation(const Vector3<T>& p_translation)
	{
		return Matrix4<T>(1, 0, 0, p_translation.x,
		                  0, 1, 0, p_translation.y,
		                  0, 0, 1, p_translation.z,
		                  0, 0, 0, 1);
	}

	template <typename T>
	constexpr Matrix4<T> Matrix4<T>::Translate(const Matrix4<T>& p_matrix, const Vector3<T>& p_translation)
	{
		return p_matrix * Matrix4<T>::Translation(p_translation);
	}

	template <typename T>
	Matrix4<T>& Matrix4<T>::Translate(const Vector3<T>& p_translation)
	{
		return *this *= Matrix4<T>::Translation(p_translation);
	}

	template <typename T>
	constexpr Matrix4<T> Matrix4<T>::RotationOnAxisX(float p_rotation)
	{
		return Matrix4<T>(1, 0, 0, 0,
		                  0, Tools::Utils::Cos(p_rotation), -Tools::Utils::Sin(p_rotation), 0,
		                  0, Tools::Utils::Sin(p_rotation), Tools::Utils::Cos(p_rotation), 0,
		                  0, 0, 0, 1);
	}

	template <typename T>
	constexpr Matrix4<T> Matrix4<T>::RotateOnAxisX(const Matrix4<T>& p_matrix, float p_rotation)
	{
		return p_matrix * Matrix4<T>::RotationOnAxisX(p_rotation);
	}

	template <typename T>
	Matrix4<T>& Matrix4<T>::RotateOnAxisX(float p_rotation)
	{
		return *this *= Matrix4<T>::RotationOnAxisX(p_rotation);
	}

	template <typename T>
	constexpr Matrix4<T> Matrix4<T>::RotationOnAxisY(float p_rotation)
	{
		return Matrix4<T>(Tools::Utils::Cos(p_rotation), 0, -Tools::Utils::Sin(p_rotation), 0,
		                  0, 1, 0, 0,
		                  Tools::Utils::Sin(p_rotation), 0, Tools::Utils::Cos(p_rotation), 0,
		                  0, 0, 0, 1);
	}

	template <typename T>
	constexpr Matrix4<T> Matrix4<T>::RotateOnAxisY(const Matrix4<T>& p_matrix, float p_rotation)
	{
		return p_matrix * Matrix4<T>::RotationOnAxisY(p_rotation);
	}

	template <typename T>
	Matrix4<T>& Matrix4<T>::RotateOnAxisY(float p_rotation)
	{
		return *this *= Matrix4<T>::RotationOnAxisY(p_rotation);
	}

	template <typename T>
	constexpr Matrix4<T> Matrix4<T>::RotationOnAxisZ(float p_rotation)
	{
		return Matrix4<T>(Tools::Utils::Cos(p_rotation), -Tools::Utils::Sin(p_rotation), 0, 0,
		                  Tools::Utils::Sin(p_rotation), Tools::Utils::Cos(p_rotation), 0, 0,
		                  0, 0, 1, 0,
		                  0, 0, 0, 1);
	}

	template <typename T>
	constexpr Matrix4<T> Matrix4<T>::RotateOnAxisZ(const Matrix4<T>& p_matrix, float p_rotation)
	{
		return p_matrix * Matrix4<T>::RotationOnAxisZ(p_rotation);
	}

	template <typename T>
	Matrix4<T>& Matrix4<T>::RotateOnAxisZ(float p_rotation)
	{
		return *this *= Matrix4<T>::RotationOnAxisZ(p_rotation);
	}

	template <typename T>
	constexpr Matrix4<T> Matrix4<T>::RotationYXZ(float p_rotation)
	{
		Matrix4<T> Xrot = Matrix4<T>::RotationOnAxisX(p_rotation);
		Matrix4<T> Yrot = Matrix4<T>::RotationOnAxisY(p_rotation);
		Matrix4<T> Zrot = Matrix4<T>::RotationOnAxisZ(p_rotation);

		return Yrot * Xrot * Zrot;
	}

	template <typename T>
	constexpr Matrix4<T> Matrix4<T>::RotateYXZ(const Matrix4<T>& p_matrix, float p_rotation)
	{
		return p_matrix * Matrix4<T>::RotationYXZ(p_rotation);
	}

	template <typename T>
	Matrix4<T>& Matrix4<T>::RotateYXZ(float p_rotation)
	{
		return *this *= Matrix4<T>::RotationYXZ(p_rotation);
	}

	template <typename T>
	constexpr Matrix4<T> Matrix4<T>::Scaling(const Vector3<T>& p_scale)
	{
		return Matrix4<T>(p_scale.x, 0, 0, 0,
		                  0, p_scale.y, 0, 0,
		                  0, 0, p_scale.z, 0,
		                  0, 0, 0, 1);
	}

	template <typename T>
	inline constexpr Matrix4<T> Matrix4<T>::Scale(const Matrix4<T>& p_matrix, const Vector3<T>& p_scale)
	{
		return p_matrix * Matrix4<T>::Scaling(p_scale);
	}

	template <typename T>
	Matrix4<T>& Matrix4<T>::Scale(const Vector3<T>& p_scale)
	{
		return *this *= Matrix4<T>::Scaling(p_scale);
	}

	template <typename T>
	Matrix4<T> Matrix4<T>::Transpose(const Matrix4<T>& p_matrix)
	{
		Matrix4<T> TransposedMatrix(p_matrix);

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				TransposedMatrix.elements[4 * j + i] = p_matrix.elements[4 * i + j];
			}
		}
		return TransposedMatrix;
	}

	template <typename T>
	Matrix4<T>& Matrix4<T>::Transpose()
	{
		Matrix4<T> TransposedMatrix(*this);

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				TransposedMatrix.elements[4 * j + i] = this->elements[4 * i + j];
			}
		}
		*this = TransposedMatrix;
		return *this;
	}

	template <typename T>
	const Matrix4<T> Matrix4<T>::Inverse(const Matrix4<T>& p_matrix)
	{
		return p_matrix.Inverse();
	}

	template <typename T>
	Matrix4<T> Matrix4<T>::Inverse() const
	{
		const float cof0 = GetMinor(elements[5], elements[9], elements[13], elements[6], elements[10], elements[14],
		                            elements[7], elements[11], elements[15]);
		const float cof1 = GetMinor(elements[1], elements[9], elements[13], elements[2], elements[10], elements[14],
		                            elements[3], elements[11], elements[15]);
		const float cof2 = GetMinor(elements[1], elements[5], elements[13], elements[2], elements[6], elements[14],
		                            elements[3], elements[7], elements[15]);
		const float cof3 = GetMinor(elements[1], elements[5], elements[9], elements[2], elements[6], elements[10],
		                            elements[3], elements[7], elements[11]);

		const float det = elements[0] * cof0 - elements[4] * cof1 + elements[8] * cof2 - elements[12] * cof3;
		if (fabs(det) <= EPSILON)
			return Matrix4<T>::Identity;
		const float cof4 = GetMinor(elements[4], elements[8], elements[12], elements[6], elements[10], elements[14],
		                            elements[7], elements[11], elements[15]);
		const float cof5 = GetMinor(elements[0], elements[8], elements[12], elements[2], elements[10], elements[14],
		                            elements[3], elements[11], elements[15]);
		const float cof6 = GetMinor(elements[0], elements[4], elements[12], elements[2], elements[6], elements[14],
		                            elements[3], elements[7], elements[15]);
		const float cof7 = GetMinor(elements[0], elements[4], elements[8], elements[2], elements[6], elements[10],
		                            elements[3], elements[7], elements[11]);

		const float cof8 = GetMinor(elements[4], elements[8], elements[12], elements[5], elements[9], elements[13],
		                            elements[7], elements[11], elements[15]);
		const float cof9 = GetMinor(elements[0], elements[8], elements[12], elements[1], elements[9], elements[13],
		                            elements[3], elements[11], elements[15]);
		const float cof10 = GetMinor(elements[0], elements[4], elements[12], elements[1], elements[5], elements[13],
		                             elements[3], elements[7], elements[15]);
		const float cof11 = GetMinor(elements[0], elements[4], elements[8], elements[1], elements[5], elements[9],
		                             elements[3], elements[7], elements[11]);

		const float cof12 = GetMinor(elements[4], elements[8], elements[12], elements[5], elements[9], elements[13],
		                             elements[6], elements[10], elements[14]);
		const float cof13 = GetMinor(elements[0], elements[8], elements[12], elements[1], elements[9], elements[13],
		                             elements[2], elements[10], elements[14]);
		const float cof14 = GetMinor(elements[0], elements[4], elements[12], elements[1], elements[5], elements[13],
		                             elements[2], elements[6], elements[14]);
		const float cof15 = GetMinor(elements[0], elements[4], elements[8], elements[1], elements[5], elements[9],
		                             elements[2], elements[6], elements[10]);

		const float detInv = 1.0f / det;
		Matrix4<float> inverse;

		inverse.elements[0] = detInv * cof0;
		inverse.elements[4] = -detInv * cof4;
		inverse.elements[8] = detInv * cof8;
		inverse.elements[12] = -detInv * cof12;
		inverse.elements[1] = -detInv * cof1;
		inverse.elements[5] = detInv * cof5;
		inverse.elements[9] = -detInv * cof9;
		inverse.elements[13] = detInv * cof13;
		inverse.elements[2] = detInv * cof2;
		inverse.elements[6] = -detInv * cof6;
		inverse.elements[10] = detInv * cof10;
		inverse.elements[14] = -detInv * cof14;
		inverse.elements[3] = -detInv * cof3;
		inverse.elements[7] = detInv * cof7;
		inverse.elements[11] = -detInv * cof11;
		inverse.elements[15] = detInv * cof15;

		return inverse;
	}

	template <typename T>
	T Matrix4<T>::Determinant(const Matrix4<T>& p_matrix)
	{
		return p_matrix.Determinant();
	}

	template <typename T>
	T Matrix4<T>::Determinant()
	{
		return elements[0] * GetMinor(elements[5], elements[9], elements[13], elements[6], elements[10], elements[14],
		                              elements[7], elements[11], elements[15])
			- elements[4] * GetMinor(elements[1], elements[9], elements[13], elements[2], elements[10], elements[14],
			                         elements[3], elements[11], elements[15])
			+ elements[8] * GetMinor(elements[1], elements[5], elements[13], elements[2], elements[6], elements[14],
			                         elements[3], elements[7], elements[15])
			- elements[12] * GetMinor(elements[1], elements[5], elements[9], elements[2], elements[6], elements[10],
			                          elements[3], elements[7], elements[11]);
	}

	template <typename T>
	float Matrix4<T>::GetMinor(float p_minor0, float p_minor1, float p_minor2, float p_minor3, float p_minor4,
	                           float p_minor5, float p_minor6, float p_minor7, float p_minor8)
	{
		return p_minor0 * (p_minor4 * p_minor8 - p_minor5 * p_minor7)
			- p_minor1 * (p_minor3 * p_minor8 - p_minor5 * p_minor6)
			+ p_minor2 * (p_minor3 * p_minor7 - p_minor4 * p_minor6);
	}
#pragma endregion

#pragma region Comparison & Conversion & Test

	template <typename T>
	inline T& Matrix4<T>::operator()(uint8_t p_row, uint8_t p_column)
	{
		if (p_row >= 4 || p_column >= 4)
			throw std::out_of_range(
				"Invalid index : " + std::to_string(p_row) + "," + std::to_string(p_column) + " is out of range");
		return elements[4 * p_row + p_column];
	}

	template <typename T>
	Vector4<T> Matrix4<T>::GetColumn(uint8_t p_column)
	{
		if (p_column >= 4)
			throw std::out_of_range("Invalid index : " + std::to_string(p_column) + " is out of range");

		return Vector4<T>(elements[p_column], elements[p_column + 4], elements[p_column + 8], elements[p_column + 12]);
	}

	template <typename T>
	Vector4<T> Matrix4<T>::GetRow(uint8_t p_row)
	{
		if (p_row >= 4)
			throw std::out_of_range("Invalid index : " + std::to_string(p_row) + " is out of range");

		return Vector4<T>(p_row * 4, p_row * 4 + 1, p_row * 4 + 2, p_row * 4 + 3);
	}

	template <typename T>
	T* Matrix4<T>::ToArray(const Matrix4<T>& p_matrix)
	{
		return p_matrix.elements;
	}

	template <typename T>
	T* Matrix4<T>::ToArray()
	{
		return elements;
	}

	template <typename T>
	std::string Matrix4<T>::ToString() const
	{
		std::stringstream ss;
		ss << elements[0] << "\t" << elements[1] << "\t" << elements[2] << "\t" << elements[3] << "\n" <<
			elements[4] << "\t" << elements[5] << "\t" << elements[6] << "\t" << elements[7] << "\n" <<
			elements[8] << "\t" << elements[9] << "\t" << elements[10] << "\t" << elements[11] << "\n" <<
			elements[12] << "\t" << elements[13] << "\t" << elements[14] << "\t" << elements[15] << "\n";
		std::string result = ss.str();
		return result;
	}

	template <typename T>
	std::string Matrix4<T>::ToString(const Matrix4<T>& p_matrix)
	{
		return p_matrix.ToString();
	}

	template <typename T>
	std::ostream& operator<<(std::ostream& p_stream, const Matrix4<T>& p_matrix)
	{
		p_stream << p_matrix.elements[0] << "\t" << p_matrix.elements[1] << "\t" << p_matrix.elements[2] << "\t" <<
			p_matrix.elements[3] << "\n" <<
			p_matrix.elements[4] << "\t" << p_matrix.elements[5] << "\t" << p_matrix.elements[6] << "\t" << p_matrix.
			elements[7] << "\n" <<
			p_matrix.elements[8] << "\t" << p_matrix.elements[9] << "\t" << p_matrix.elements[10] << "\t" << p_matrix.
			elements[11] << "\n" <<
			p_matrix.elements[12] << "\t" << p_matrix.elements[13] << "\t" << p_matrix.elements[14] << "\t" << p_matrix.
			elements[15] << "\n";
		return p_stream;
	}

#pragma endregion
}

#endif
