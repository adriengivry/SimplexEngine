/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _COLOR_H
#define _COLOR_H

#include <stdint.h>
#include <tuple>

namespace Rasterizer::Data
{
	/**
	* A simple struct that represent a color
	*/
	struct Color final
	{
		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color White;
		static const Color Black;
		static const Color Yellow;
		static const Color Cyan;
		static const Color Magenta;

		/**
		* Create a color with given values
		* @param p_r (Red value)
		* @param p_g (Green value)
		* @param p_b (Blue value)
		*/
		Color(uint8_t p_r = 0, uint8_t p_g = 0, uint8_t p_b = 0, uint8_t p_a = 255);

		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;

		/**
		* Return a normalized version (As a tuple of float between 0.f and 1.f) of the current color
		*/
		std::tuple<float, float, float, float> GetNormalized() const;

		/**
		* Pack data to uint32_t
		*/
		uint32_t Pack() const;
	};
}

#endif // _COLOR_H
