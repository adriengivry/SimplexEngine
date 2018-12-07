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
		virtual void UpdateUniforms(const Components::CameraComponent& p_cameraComponent, const Components::MeshComponent& p_meshComponent);
	};
}

#endif // _LAMBERTMATERIAL_H