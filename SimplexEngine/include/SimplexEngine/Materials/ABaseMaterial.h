/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _ABASEMATERIAL_H
#define _ABASEMATERIAL_H

#include "SimplexEngine/API/Export.h"
#include "SimplexEngine/Materials/AMaterial.h"
#include "SimplexEngine/Materials/MaterialData.h"
#include "SimplexEngine/Shaders/AShader.h"
#include "SimplexEngine/Components/CameraComponent.h"
#include "SimplexEngine/Components/MeshComponent.h"

namespace SimplexEngine::Materials
{
	/**
	* The base class for any material of this project.
	* A material is a set of uniforms binded with a shader
	*/
	template <typename ShaderClass>
	class ABaseMaterial : public AMaterial
	{
		static_assert(std::is_base_of<Shaders::AShader, ShaderClass>::value, "ShaderClass must be a descendant of AShader");

	public:
		/**
		* Base material constructor
		*/
		ABaseMaterial() { CreateShaderInstance<ShaderClass>(); }

		/**
		* Implement this function to determine the behaviour of the material
		* when UpdateUniforms is called
		* @param p_materialData
		*/
		virtual void UpdateUniforms(const MaterialData& p_materialData) = 0;

	protected:
		/**
		* Define the shader class to use
		* @note you only have to give a shader type, no params are requierd
		*/
		template<typename ShaderClass>
		void CreateShaderInstance() { m_shaderInstance = std::make_unique<ShaderClass>(); }

		/**
		* Set a uniform value identified by the given name
		* @param p_name
		* @param p_value
		*/
        template<typename T>
		void SetUniform(int p_index, T p_value)
        {
            m_shaderInstance->SetUniform(p_index, p_value);
        }
	};
}


#endif // _ABASEMATERIAL_H