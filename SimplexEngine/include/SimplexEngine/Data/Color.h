/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _COLOR_H
#define _COLOR_H

#include <stdint.h>
#include <tuple>

#include <glm/glm.hpp>

#include "SimplexEngine/API/Export.h"

namespace SimplexEngine::Data
{
	/**
	* A simple struct that represent a color
	*/
	struct API_SIMPLEXENGINE Color final
	{
		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color White;
		static const Color Black;
		static const Color Yellow;
		static const Color Cyan;
		static const Color Magenta;


		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;

		/**
		* Create a color with given integer values
		* @param p_r (Red value [0 to 255])
		* @param p_g (Green value [0 to 255])
		* @param p_b (Blue value [0 to 255])
		* @param p_a (Alpha value [0 to 255])
		*/
		Color(uint8_t p_r = 0, uint8_t p_g = 0, uint8_t p_b = 0, uint8_t p_a = 255);

		/**
		* Create a color from normalized color
		* @param p_normalizedColor
		*/
		Color(const glm::vec4& p_normalizedColor);

		/**
		* Create a color from normalized color (Alpha set to 255)
		* @param p_normalizedColor
		*/
		Color(const glm::vec3& p_normalizedColor);

		/**
		* Create a color from a packed uint32_t
		* @param p_packedData
		*/
		Color(uint32_t p_packedData);

		/**
		* Return a normalized version (glm::vec4) of the current color
		*/
        inline glm::vec4 GetNormalizedVec4() const
        {
            glm::vec4 frgba(static_cast<float>(r), static_cast<float>(g), static_cast<float>(b), static_cast<float>(a));

            __m128 m_frgba = _mm_load_ps(&frgba.x);
            __m128 m_cbits = _mm_set1_ps(1 / 255.0f);

            _mm_store_ps(&frgba.x, _mm_mul_ps(m_frgba, m_cbits));

            return frgba;
        }

		/**
		* Return a normalized version (glm::vec3) of the current color
		* @param p_alpha is lost!
		*/
        inline glm::vec3 GetNormalizedVec3() const
        {
            return glm::vec3(r / 255.f, g / 255.f, b / 255.f);
        }

		/**
		* Pack data to uint32_t
		*/
        inline uint32_t Pack() const
        {
            return (r << 24) | (g << 16) | (b << 8) | a;
        }

		/**
		* Mix two colors
		* @param p_color1
		* @param p_color2
		* @param p_alpha
		*/
        static inline Color Mix(const Color& p_color1, const Color& p_color2, float p_alpha)
        {
            return Data::Color(glm::mix(p_color1.GetNormalizedVec3(), p_color2.GetNormalizedVec3(), p_alpha));
        }
	};
}

#endif // _COLOR_H
