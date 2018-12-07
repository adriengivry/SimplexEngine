/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _ASHADER_H
#define _ASHADER_H

#include <unordered_map>
#include <variant>
#include <string>
#include <algorithm>

#include "Rasterizer/Data/Vertex.h"

namespace Rasterizer::Shaders
{
	/**
	* The AShader class is the base class for any shader of this project.
	* A shader is a simple set of methods that can modify vertices and pixels
	* of the rendering pipeline
	*/
	class AShader
	{
	public:
		/* A simple typedef for a variant of every types that a shader can use */
		using ShaderType = std::variant<int, float, glm::vec2, glm::vec3, glm::vec4, glm::mat2, glm::mat3, glm::mat4>;

		/**
		* The vertex modifier is where the vertex is modified.
		* It is called before the rasterization stage
		* @param p_vertex
		*/
		virtual glm::vec4 VertexModifier(const Data::Vertex& p_vertex, uint8_t p_vertexID) = 0;

		/**
		* The fragment modifier is where every pixels are modified.
		* It is called after the rasterization stage
		* @param p_barycentricCoords (Barycentric coordinates of the current fragment)
		*/
		virtual glm::vec3 FragmentModifier(const glm::vec3& p_barycentricCoords) = 0;

		/**
		* Send a value to the shader (Identified by the given name)
		* to use it in vertex and fragment modifier
		* @param p_name
		* @param p_value
		*/
		void SetUniform(const std::string& p_name, ShaderType p_value);

		/**
		* Clear every uniforms stored in this shader
		*/
		void ClearUniforms();

		/**
		* Clear any internal data in this shader
		*/
		void ClearInternal();

		/**
		* Clear any data stored in this shader
		*/
		void ClearAll();

	protected:
		/**
		* Return the value of the uniform identified by the given name
		* @param p_name
		*/
		ShaderType GetUniform(const std::string& p_name);

		/**
		* Return the value of a stored data identified by the given name
		* @param p_name
		*/
		ShaderType GetInternal(const std::string& p_name);

		/**
		* Store a value in the shader for later use. It can be
		* retrieved from the vertex and the fragment shader
		* @param p_name
		* @param p_value
		*/
		void SetInternal(const std::string& p_name, ShaderType p_value);

	private:
		std::unordered_map<std::string, ShaderType> m_uniforms;
		std::unordered_map<std::string, ShaderType> m_internal;
	};
}

#endif // _ASHADER_H