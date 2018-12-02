/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _VERTEX_H
#define _VERTEX_H

#include <AltMath/AltMath.h>

namespace Rasterizer::Data
{
	/**
	* The vertex struct represent a point of the geometry of a triangle
	*/
	struct Vertex final
	{
		/**
		* Constructor for the vertex struct
		* @param p_x
		* @param p_y
		* @param p_z
		* @param p_nx
		* @param p_ny
		* @param p_nz
		*/
		Vertex(float p_x, float p_y, float p_z, float p_nx = 0.0f, float p_ny = 0.0f, float p_nz = 0.0f);

		AltMath::Vector3f position;
		AltMath::Vector3f normal;
	};
}

#endif // _VERTEX_H