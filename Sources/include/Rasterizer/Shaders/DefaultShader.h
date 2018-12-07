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
		virtual glm::vec4 VertexModifier(const Data::Vertex& p_vertex) override;
		virtual glm::vec3 FragmentModifier() override;
	};
}

#endif // _DEFAULTSHADER_H