/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _NORMALSHADER_H
#define _NORMALSHADER_H

#include "Rasterizer/Shaders/AShader.h"

namespace Rasterizer::Shaders
{
	/**
	* The default shader to use in this project
	*/
	class NormalShader final : public AShader
	{
		virtual glm::vec4 VertexModifier(const Data::Vertex& p_vertex) override;
		virtual glm::vec3 FragmentModifier() override;
	};
}

#endif // _NORMALSHADER_H