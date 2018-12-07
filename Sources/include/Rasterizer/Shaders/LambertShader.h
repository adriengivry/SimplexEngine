/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _LAMBERTSHADER_H
#define _LAMBERTSHADER_H

#include "Rasterizer/Shaders/AShader.h"

namespace Rasterizer::Shaders
{
	class LambertShader final : public AShader
	{
		virtual glm::vec4 VertexModifier(const Data::Vertex & p_vertex, uint8_t p_vertexID) override;
		virtual glm::vec3 FragmentModifier(const glm::vec3 & p_barycentricCoords) override;

		/**
		* Calculate lambert
		* @param p_fragmentNormal
		* @param p_lightPosition
		*/
		float Lambert(const glm::vec3& p_fragmentNormal, const glm::vec3& p_lightPosition);
	};
}

#endif // _LAMBERTSHADER_H