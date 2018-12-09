/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _BUFFER2D_H
#define _BUFFER2D_H

#include <vector>

#include "SimplexEngine/API/Export.h"

namespace SimplexEngine::Buffers
{
	/**
	* A generic base for any 2D Buffer
	*/
	template <typename T>
	struct API_SIMPLEXENGINE Buffer2D
	{
		/**
		* Constructor of the buffer structure
		* @param p_width
		* @param p_height
		*/
		Buffer2D(uint32_t p_width, uint32_t p_height) : width(p_width), height(p_height), m_bufferSize(width * height), m_bufferSizeInBytes(static_cast<uint32_t>(m_bufferSize * sizeof(T))) { data = new T[m_bufferSize]; }

		/**
		* Free the buffer
 		*/
		virtual ~Buffer2D() { delete[] data; }

		/* Actual data */
		const uint32_t width;
		const uint32_t height;
		T* data;

		/**
		* Access an element of the buffer
		* @param p_x
		* @param p_y
		*/
		T& GetElement(uint32_t p_x, uint32_t p_y) const { return data[p_y * width + p_x]; }

		/**
		* Set an element value of the buffer
		* @param p_x
		* @param p_y
		* @param p_value
		*/
		void SetElement(uint32_t p_x, uint32_t p_y, const T& p_value) { data[p_y * width + p_x] = p_value; }

		/**
		* Clear the buffer (Fill with 0)
		*/
		void Clear() { memset(data, 0, m_bufferSizeInBytes); }

	protected:
		const uint32_t m_bufferSize;
		const uint32_t m_bufferSizeInBytes; 
	};
}

#endif // _BUFFER2D_H