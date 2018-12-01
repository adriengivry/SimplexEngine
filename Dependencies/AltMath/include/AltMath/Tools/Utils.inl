/**
 * Project AltMath
 * @author GP2021
 * @version 1.0.0
 */

#pragma once
#ifndef _UTILS_INL
#define _UTILS_INL

#include "Utils.h"
#include <cmath>
#include <type_traits>

template<typename T>
inline T AltMath::Tools::Utils::Pow(T p_value, int p_exp)
{
	static_assert(std::is_arithmetic<T>::value, "The value to pow must be arithmetic");
	return static_cast<T>(std::pow(p_value, p_exp));
}

template<typename T>
inline T AltMath::Tools::Utils::Pow(T p_value, float p_exp)
{
	static_assert(std::is_arithmetic<T>::value, "The value to pow must be arithmetic");
	return static_cast<T>(std::pow(p_value, p_exp));
}

template <typename T>
inline T AltMath::Tools::Utils::SquareRoot(T p_value)
{
	static_assert(std::is_arithmetic<T>::value, "The value to root must be arithmetic");
	return static_cast<T>(std::sqrt(p_value));
}

template <typename T>
T AltMath::Tools::Utils::SquareRootF(T p_value)
{
	static_assert(std::is_arithmetic<T>::value, "The value to root must be arithmetic");
	return static_cast<T>(std::sqrtf(p_value));
}

template<typename T>
inline T AltMath::Tools::Utils::Root(T p_value, float p_nRoot)
{
	static_assert(std::is_arithmetic<T>::value, "The value to root must be arithmetic");
	return static_cast<T>(std::pow(p_value, 1 / p_nRoot));
}

template<typename T>
inline T AltMath::Tools::Utils::Abs(T p_value)
{
	static_assert(std::is_arithmetic<T>::value, "The value to Abs must be arithmetic");
	return static_cast<T>(std::abs(p_value));
}

#endif // _UTILS_INL
