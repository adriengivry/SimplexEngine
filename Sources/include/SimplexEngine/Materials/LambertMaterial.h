/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _LAMBERTMATERIAL_H
#define _LAMBERTMATERIAL_H

#include "SimplexEngine/Shaders/LambertShader.h"
#include "SimplexEngine/Materials/ABaseMaterial.h"

namespace SimplexEngine::Materials
{
	class LambertMaterial final : public ABaseMaterial<Shaders::LambertShader>
	{
	public:
		virtual void UpdateUniforms(const Components::CameraComponent& p_cameraComponent, const Components::MeshComponent& p_meshComponent);
	};
}

#endif // _LAMBERTMATERIAL_H