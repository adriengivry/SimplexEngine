/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _AMATERIAL_H
#define _AMATERIAL_H

#include "SimplexEngine/API/Export.h"
#include "SimplexEngine/Shaders/AShader.h"
#include "SimplexEngine/Components/CameraComponent.h"
#include "SimplexEngine/Materials/MaterialData.h"

namespace SimplexEngine::Materials
{
	/**
	* Material abstract class
	*/
	class API_SIMPLEXENGINE AMaterial
	{
	public:
		/**
		* Implement this function to determine the behaviour of the material
		* when UpdateUniforms is called
		* @param p_materialData
		*/
		virtual void UpdateUniforms(const MaterialData& p_materialData) = 0;

		/**
		* Return the binded shader instance
		*/
		Shaders::AShader& GetShaderInstance();

	protected:
		std::unique_ptr<Shaders::AShader> m_shaderInstance;
	};
}

#endif // _AMATERIAL_H