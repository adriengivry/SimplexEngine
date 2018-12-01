/**
 * Project AltMath
 * @author GP2021
 * @version 1.0.0
 */

#pragma once
#ifndef _RANDOM_H
#define _RANDOM_H

#pragma warning(push)
#pragma warning(disable: 4251)

#include <random>
#include "AltMath/export.h"

namespace AltMath
{
	namespace Tools
	{
		/**
		 * Provides some static random number generation
		 */
		class ALTMATH_API Random final
		{
		private:
			static std::default_random_engine s_generator;

		public:
			/* Desactivate the constructor (Un-instanciable static class) */
			Random() = delete;

            /**
            * Generate a random between two given integers (Closed interval)
            * @param p_min
            * @param p_max
            */
            template<typename T>
            static T GenerateInt(T p_min, T p_max);

            /**
            * Generate a random between two given floats (Closed interval)
            * @param p_min
            * @param p_max
            */
            template<typename T>
            static T GenerateFloat(T p_min, T p_max);

			/**
			 * Verify if the percentage is satisfied
			 * @param p_percentage
			 */
            static bool CheckPercentage(float p_percentage);
		};

	}
}
#include "Random.inl"

#pragma warning(pop)
#endif //_RANDOM_H