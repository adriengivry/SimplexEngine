/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _NORMALMATERIAL_H
#define _NORMALMATERIAL_H

#include "SimplexEngine/API/Export.h"
#include "SimplexEngine/Shaders/NormalShader.h"
#include "SimplexEngine/Materials/ABaseMaterial.h"

namespace SimplexEngine::Materials
{
	class API_SIMPLEXENGINE NormalMaterial final : public ABaseMaterial<Shaders::NormalShader>
	{
	public:
		virtual void UpdateUniforms(const MaterialData& p_materialData);
	};
}

#endif // _LAMBERTMATERIAL_H