/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _DEFAULTSHADER_H
#define _DEFAULTSHADER_H

#include "Rasterizer/FakeGL/AShader.h"

namespace Rasterizer::FakeGL
{
	/**
	* The default shader to use in this project
	*/
	class DefaultShader final : public AShader
	{
		/**
		* DefaultShader implementation of the VertexModifier
		* @param p_vertex
		*/
		virtual glm::vec4 VertexModifier(const Data::Vertex& p_vertex) override;

		/**
		* DefaultShader implementation of the FragmentModifier
		*/
		virtual glm::vec3 FragmentModifier() override;
	};
}

#endif // _DEFAULTSHADER_H