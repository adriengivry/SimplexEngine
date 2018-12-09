/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Buffers/DepthBuffer.h"

SimplexEngine::Buffers::DepthBuffer::DepthBuffer(uint32_t p_width, uint32_t p_height)
	: Buffer2D(p_width, p_height)
{
}

void SimplexEngine::Buffers::DepthBuffer::Clear()
{
	for (uint32_t i = 0; i < m_bufferSize; ++i)
		data[i] = std::numeric_limits<float>::infinity();
}
