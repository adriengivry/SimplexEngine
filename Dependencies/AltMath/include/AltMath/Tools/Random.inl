/**
* Project AltMath
* @author GP2021
* @version 1.0.0
*/

#pragma once
#ifndef _RANDOM_INL
#define _RANDOM_INL

#include "Utils.h"
#include <cmath>
#include <type_traits>

namespace AltMath
{
    namespace Tools
    {
        template<typename T>
        T Random::GenerateInt(T p_min, T p_max)
        {
            static_assert(std::is_arithmetic<T>::value && std::is_integral<T>::value, "The value to GenerateInt must be an integer");
            std::uniform_int_distribution<T> distribution(p_min, p_max);
            return distribution(s_generator);
        }

        template<typename T>
        T Random::GenerateFloat(T p_min, T p_max)
        {
            static_assert(std::is_arithmetic<T>::value && std::is_floating_point<T>::value, "The value to Generate must be a floating point");
            std::uniform_real_distribution<T> distribution(p_min, p_max);
            return distribution(s_generator);
        }
    }
}


#endif //!_RANDOM_INL