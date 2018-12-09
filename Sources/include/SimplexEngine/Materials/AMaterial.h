/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _AMATERIAL_H
#define _AMATERIAL_H

#include "SimplexEngine/Shaders/AShader.h"
#include "SimplexEngine/Components/CameraComponent.h"

namespace SimplexEngine::Components { class MeshComponent; }

namespace SimplexEngine::Materials
{
	/**
	* Material abstract class
	*/
	class AMaterial
	{
	public:
		/**
		* Implement this function to determine the behaviour of the material
		* when UpdateUniforms is called
		* @param p_cameraComponent
		* @param p_meshComponent
		*/
		virtual void UpdateUniforms(const Components::CameraComponent& p_cameraComponent, const Components::MeshComponent& p_meshComponent) = 0;

		/**
		* Return the binded shader instance
		*/
		Shaders::AShader& GetShaderInstance();

	protected:
		std::unique_ptr<Shaders::AShader> m_shaderInstance;
	};
}

#endif // _AMATERIAL_H