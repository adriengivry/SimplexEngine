/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _LAMBERTMATERIAL_H
#define _LAMBERTMATERIAL_H

#include "SimplexEngine/API/Export.h"
#include "SimplexEngine/Shaders/LambertShader.h"
#include "SimplexEngine/Materials/ABaseMaterial.h"

namespace SimplexEngine::Materials
{
	/**
	* A simple material that send data to the lambert shader
	*/
	class API_SIMPLEXENGINE LambertMaterial final : public ABaseMaterial<Shaders::LambertShader>
	{
	public:
		virtual void UpdateUniforms(const MaterialData& p_materialData);
	};
}

#endif // _LAMBERTMATERIAL_H