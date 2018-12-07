/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _AMATERIAL_H
#define _AMATERIAL_H

#include "Rasterizer/Shaders/AShader.h"
#include "Rasterizer/Entities/Model.h"
#include "Rasterizer/Entities/Camera.h"

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
		* @param p_camera
		* @param p_model
		*/
		virtual void UpdateUniforms(const Entities::Camera& p_camera, const Entities::Model& p_model) = 0;

		/**
		* Return the binded shader instance
		*/
		Shaders::AShader& GetShaderInstance();

	protected:
		std::unique_ptr<Shaders::AShader> m_shaderInstance;
	};
}

#endif // _AMATERIAL_H