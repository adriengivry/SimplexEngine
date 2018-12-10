/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _LAMBERTSHADER_H
#define _LAMBERTSHADER_H

#include "SimplexEngine/API/Export.h"
#include "SimplexEngine/Shaders/AShader.h"

namespace SimplexEngine::Shaders
{
	class API_SIMPLEXENGINE LambertShader final : public AShader
	{
	public:
		virtual glm::vec4 VertexModifier(const Data::Vertex & p_vertex) override;
		virtual glm::vec3 FragmentModifier() const override;

		/**
		* Calculate lambert
		* @param p_fragmentNormal
		* @param p_lightPosition
		*/
		float Lambert(const glm::vec3& p_fragmentNormal, const glm::vec3& p_lightPosition) const;
	};
}

#endif // _LAMBERTSHADER_H