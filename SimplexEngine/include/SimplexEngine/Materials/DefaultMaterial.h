/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _DEFAULTMATERIAL_H
#define _DEFAULTMATERIAL_H

#include "SimplexEngine/API/Export.h"
#include "SimplexEngine/Materials/ABaseMaterial.h"
#include "SimplexEngine/Actors/Actor.h"

/**
* This utility macro replace the DefineMaterial method call by USE_SHADER(ShaderClass)
* @param ShaderClass (Must be a Shader type)
*/
#define USE_SHADER(ShaderClass) DefineMaterial<SimplexEngine::Materials::DefaultMaterial<ShaderClass>>()

constexpr uint8_t kMVP = 0;
constexpr uint8_t kModel = 1;
constexpr uint8_t kTime = 2;
constexpr uint8_t kBaseColor = 3;

namespace SimplexEngine::Materials
{
	/**
	* A simple material that send mvp and model matrix to the bound shader
	*/
	template<typename ShaderClass>
	class DefaultMaterial final : public ABaseMaterial<ShaderClass>
	{
	public:
		virtual void UpdateUniforms(const MaterialData& p_materialData)
		{
			this->SetUniform(kMVP, p_materialData.mainCamera.GetViewProjectionMatrix() * p_materialData.mesh.owner->transform.GetWorldMatrix());
			this->SetUniform(kModel, p_materialData.mesh.owner->transform.GetWorldMatrix());
			this->SetUniform(kTime, p_materialData.totalTime);
			this->SetUniform(kBaseColor, baseColor.GetNormalizedVec4());
		}

		Data::Color baseColor = Data::Color::White;
	};
}

#endif // _DEFAULTMATERIAL_H