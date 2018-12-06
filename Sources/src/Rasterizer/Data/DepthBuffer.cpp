/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Data/DepthBuffer.h"

Rasterizer::Data::DepthBuffer::DepthBuffer(uint32_t p_width, uint32_t p_height)
	: Buffer2D(p_width, p_height)
{
}

void Rasterizer::Data::DepthBuffer::Clear()
{
	for (uint32_t i = 0; i < m_bufferSize; ++i)
		data[i] = std::numeric_limits<float>::infinity();
}
