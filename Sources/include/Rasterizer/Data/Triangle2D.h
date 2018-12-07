/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _TRIANGLE2D_H
#define _TRIANGLE2D_H

#include <tuple>

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
		* Create a triangle with the given vertices
		* @param p_vertex1
		* @param p_vertex2
		* @param p_vertex3
		*/
		Triangle2D(const glm::vec2& p_vertex1, const glm::vec2& p_vertex2, const glm::vec2& p_vertex3);

		/**
		* Update barycentric
		*/
		void PreComputeBarycentric();

		/**
		* Calculate the area of the triangle (Calculated with cross product, can be negative)
		*/
		float GetArea() const;

		/**
		* Calculate a bounding box for the triangle
		*/
		BoundingBox GetBoundingBox() const;

		/**
		* Return barycentric coordinates for the given point
		* @param p_point
		*/
		glm::vec3 GetBarycentricCoordinates(const glm::vec2& p_point, uint8_t p_referenceVertex = 0) const;

	private:
		/* Triangle vertices */
		glm::vec2 m_vertices[3];

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