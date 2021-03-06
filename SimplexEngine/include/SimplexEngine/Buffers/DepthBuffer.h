/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _DEPTHBUFFER_H
#define _DEPTHBUFFER_H

#include "SimplexEngine/API/Export.h"
#include "SimplexEngine/Buffers/Buffer2D.h"

namespace SimplexEngine::Buffers
{
	/**
	* The depth buffer is a structure that contains informations about depth, stored in a vector.
	*/
	struct API_SIMPLEXENGINE DepthBuffer final : public Buffer2D<float>
	{
		/**
		* Constructor of the depth buffer structure
		* @param p_width
		* @param p_height
		*/
		DepthBuffer(uint32_t p_width, uint32_t p_height);

		/**
		* Clear the depth buffer by settings every floats to infinite
		*/
		void Clear();
	};
}

#endif // _DEPTHBUFFER_H