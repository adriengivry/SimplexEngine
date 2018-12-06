/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _TRIANGLE2D_H
#define _TRIANGLE2D_H

#include "Rasterizer/Entities/Camera.h"
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
		using BoundingBox = std::tuple<int32_t, int32_t, int32_t, int32_t>;

		/**
		* Create a triangle with the given points
		* @param p_firstPoint
		* @param p_secondPoint
		* @param p_thirdPoint
		*/
		Triangle2D(const glm::vec2& p_firstPoint, const glm::vec2& p_secondPoint, const glm::vec2& p_thirdPoint);

		/**
		* Calculate the area of the triangle
		*/
		float CalculateArea();

		/**
		* Update barycentric
		*/
		void UpdateBarycentric();

		/**
		* Calculate a bounding box for the triangle
		*/
		BoundingBox GetBoundingBox();

		/**
		*
		*/
		glm::vec3 Barycentric(const glm::vec2& p_point);

	private:
		glm::vec2 m_points[3];

		/* Barycentric calculation relatives */
		glm::vec2 m_V0;
		glm::vec2 m_V1;
		float m_d00;
		float m_d01;
		float m_d10;
		float m_d11;
		float m_Denom;
	};
}

#endif // _TRIANGLE2D_H