/**
 * Project AltMath
 * @author GP2021
 * @version 1.0.0
 */

#pragma once
#ifndef _UTILS_H
#define _UTILS_H

#include "AltMath/export.h"

namespace AltMath
{
	namespace Tools
	{
		/**
		 * Utils class provides some simple mathematics tools, such as operations, pow, root, trigonometry stuffs...
		 */
		class ALTMATH_API Utils final
		{
		public:
            Utils() = delete;


			/**
			 * Convert the given angle to radians
			 * @param p_angle (In degrees)
			 */
			static float ToRadians(float p_angle);

			/**
			 * Convert the given angle to degrees
			 * @param p_angle (In radians)
			 */
            static float ToDegrees(float p_angle);

			/**
			 * Linearly interpolates between two values
			 * @param p_a
			 * @param p_b
			 * @param p_alpha
			 */
            static float Lerp(float p_a, float p_b, float p_alpha);

			/**
			 * Return the pow of a numeric value with an integer exponent
			 * @param p_value
			 * @param p_exp
			 */
			template<typename T>
            static T Pow(T p_value, int p_exp);

			/**
			* Return the pow of a numeric value with a float exponent
			* @param p_value
			* @param p_exp
			*/
			template<typename T>
            static T Pow(T p_value, float p_exp);

			/**
			* Return the square root of a numeric value
			* @param p_value
			*/
			template<typename T>
			static T SquareRoot(T p_value);

			/**
			* Return the square root of a numeric value with float precision
			* @param p_value
			*/
			template<typename T>
			static T SquareRootF(T p_value);

			/**
			 * Return the root of a numeric value
			 * @param p_value
			 * @param p_nRoot
			 */
			template<typename T>
            static T Root(T p_value, float p_nRoot);

			/**
			 * Return the greatest common divider of the two given integers
			 * @param p_a
			 * @param p_b
			 */
            static int GreatestCommonDivider(int p_a, int p_b);

			/**
			 * Return the smallest common divider of the two given integers
			 * @param p_a
			 * @param p_b
			 */
            static int LeastCommonMultiple(int p_a, int p_b);

			/**
			 * Return the decimal part of a float as an integer
			 * @param p_value
			 */
            static float GetDecimalPart(float p_value);

			/**
			 * Return the absolute value of a numeric value
			 * @param p_value
			 */
			template<typename T>
            static T Abs(T p_value);

			/**
			 * Mathematic sinus implementation
			 * @param p_value
			 */
            static float Sin(float p_value);

			/**
			* Mathematic sinus implementation with float precision
			* @param p_value
			*/
			static float SinF(float p_value);

			/**
			 * Mathematic cosinus implementation
			 * @param p_value
			 */
            static float Cos(float p_value);

			/**
			* Mathematic cosinus implementation with float precision
			* @param p_value
			*/
			static float CosF(float p_value);

			/**
			 * Mathematic tangente implementation
			 * @param p_value
			 */
            static float Tan(float p_value);

			/**
			 * Mathematic arc cosinus implementation
			 * @param p_value
			 */
            static float Arccos(float p_value);

			/**
			 * Mathematic arc sinus implementation
			 * @param p_value
			 */
            static float Arcsin(float p_value);

			/**
			 * Mathematic arc tangente implementation
			 * @param p_value
			 */
            static float Arctan(float p_value);

			/**
			* Mathematic arc tangente implementation
			* @param p_valueYx
			* @param p_valueXx
			*/
			static float Arctan2(float p_valueYx, float p_valueXx);
		};
	}
}

#include "Utils.inl"

#endif //_UTILS_H