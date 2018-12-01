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
		*/
		Vertex(float p_x, float p_y, float p_z);

		AltMath::Vector3f position;
	};
}

#endif // _VERTEX_H