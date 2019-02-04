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

/**
* This utility macro replace the DefineMaterial method call by USE_SHADER(ShaderClass)
* @param ShaderClass (Must be a Shader type)
*/
#define USE_SHADER(ShaderClass) DefineMaterial<SimplexEngine::Materials::DefaultMaterial<ShaderClass>>()

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
			this->SetUniform("mvp", p_materialData.mainCamera.GetViewProjectionMatrix() * p_materialData.mesh.owner->transform.GetWorldMatrix());
			this->SetUniform("modelMatrix", p_materialData.mesh.owner->transform.GetWorldMatrix());
			this->SetUniform("time", p_materialData.totalTime);
		}
	};
}

#endif // _DEFAULTMATERIAL_H