/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _AMATERIAL_H
#define _AMATERIAL_H

#include "Rasterizer/Shaders/AShader.h"
#include "Rasterizer/Components/CameraComponent.h"
#include "Rasterizer/Components/MeshComponent.h"

namespace Rasterizer::Materials
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