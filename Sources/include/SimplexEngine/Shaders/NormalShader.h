/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _NORMALSHADER_H
#define _NORMALSHADER_H

#include "SimplexEngine/Shaders/AShader.h"

namespace SimplexEngine::Shaders
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