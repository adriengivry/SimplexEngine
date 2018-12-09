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
#include "SimplexEngine/Shaders/AShader.h"

namespace SimplexEngine::Materials
{
	/**
	* The base class for any material of this project.
	* A material is a set of uniforms binded with a shader
	*/
	template <typename ShaderClass>
	class API_SIMPLEXENGINE ABaseMaterial : public AMaterial
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
		* @param p_cameraComponent
		* @param p_meshComponent
		*/
		virtual void UpdateUniforms(const Components::CameraComponent& p_cameraComponent, const Components::MeshComponent& p_meshComponent) = 0;

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
		void SetUniform(const std::string& p_name, const Shaders::AShader::ShaderValue& p_value) { m_shaderInstance->SetUniform(p_name, p_value); }
	};
}


#endif // _ABASEMATERIAL_H