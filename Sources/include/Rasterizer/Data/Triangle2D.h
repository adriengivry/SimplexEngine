/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _TRIANGLE2D_H
#define _TRIANGLE2D_H

#include "Rasterizer/Data/Vertex.h"

namespace Rasterizer::Data
{
	/**
	* The Triangle2D class is a simple class to
	* create a triangle and effectuate some calculations with
	*/
	class Triangle2D final
	{
	public:
		/**
		* Create a triangle from screen projection
		* @param p_firstVertex
		* @param p_secondVertex
		* @param p_thirdVertex
		*/
		Triangle2D(const Data::Vertex& p_firstVertex, const Data::Vertex& p_secondVertex, const Data::Vertex& p_thirdVertex);

		/**
		* Create a triangle with the given points and
		* calculate his area
		* @param p_firstPoint
		* @param p_secondPoint
		* @param p_thirdPoint
		*/
		Triangle2D(const AltMath::Vector2i& p_firstPoint, const AltMath::Vector2i& p_secondPoint, const AltMath::Vector2i& p_thirdPoint);

		/**
		* Calculate the area of the triangle
		*/
		float CalculateArea();

		/**
		* Calculate the area of a triangle defined by 3 points
		* @param p_point1
		* @param p_point2
		* @param p_point3
		*/
		static float CalculateArea(const AltMath::Vector2i& p_point1, const AltMath::Vector2i& p_point2, const AltMath::Vector2i& p_point3);

		/**
		* Verify if a point is in the triangle
		*/
		bool IsPointIn(const AltMath::Vector2i& p_point);

	private:
		AltMath::Vector2i m_points[3];

		float m_area;
	};
}

#endif // _TRIANGLE2D_H