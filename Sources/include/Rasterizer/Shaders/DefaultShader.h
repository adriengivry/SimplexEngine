/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _DEFAULTSHADER_H
#define _DEFAULTSHADER_H

#include "Rasterizer/Shaders/AShader.h"

namespace Rasterizer::Shaders
{
	/**
	* The default shader to use in this project
	*/
	class DefaultShader final : public AShader
	{
		virtual glm::vec4 VertexModifier(const Data::Vertex& p_vertex, uint8_t p_vertexID) override;
		virtual glm::vec3 FragmentModifier(const glm::vec3& p_barycentricCoords) override;
	};
}

#endif // _DEFAULTSHADER_H