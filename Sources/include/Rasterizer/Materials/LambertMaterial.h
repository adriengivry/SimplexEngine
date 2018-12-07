/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _LAMBERTMATERIAL_H
#define _LAMBERTMATERIAL_H

#include "Rasterizer/Shaders/LambertShader.h"
#include "Rasterizer/Materials/ABaseMaterial.h"

namespace Rasterizer::Materials
{
	class LambertMaterial final : public ABaseMaterial<Shaders::LambertShader>
	{
	public:
		/**
		* Update uniforms
		* @param p_camera
		* @param p_model
		*/
		virtual void UpdateUniforms(const Entities::Camera & p_camera, const Entities::Model & p_model) override;
	};
}

#endif // _LAMBERTMATERIAL_H