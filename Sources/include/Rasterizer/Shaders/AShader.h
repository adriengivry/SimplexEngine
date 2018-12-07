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
#include <array>

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
		* Process a vertex
		*/
		glm::vec4 ProcessVertex(const Data::Vertex& p_vertex, uint8_t p_vertexID);

		/**
		* The vertex modifier is where the vertex is modified.
		* It is called before the rasterization stage
		* @param p_vertex
		*/
		virtual glm::vec4 VertexModifier(const Data::Vertex& p_vertex) = 0;

		/**
		* Process interpolation for all varying data and output to fragmentData
		* @param p_barycentricCoords
		*/
		void ProcessInterpolation(const glm::vec3& p_barycentricCoords);

		/**
		* The fragment modifier is where every pixels are modified.
		* It is called after the rasterization stage
		*/
		virtual glm::vec3 FragmentModifier() = 0;

		/**
		* Send a value to the shader (Identified by the given name)
		* to use it in vertex and fragment modifier
		* @param p_name
		* @param p_value
		*/
		void SetUniform(const std::string& p_name, ShaderType p_value);

		/**
		* Clear any data stored in this shader
		*/
		void ClearData();

	protected:
		/**
		* Return the value of the uniform identified by the given name
		* @param p_name
		*/
		template<typename T>
		T GetUniform(const std::string& p_name) { return std::get<T>(m_uniforms[p_name]); }

		/**
		*
		*/
		void SetVarying(const std::string& p_name, ShaderType p_value);

		/**
		*
		*/
		void SetFlat(const std::string& p_name, ShaderType p_value);

		/**
		*
		*/
		template<typename T>
		T GetVarying(const std::string& p_name) { return std::get<T>(m_interpolatedVarying[p_name]); }

		/**
		*
		*/
		template<typename T>
		T GetFlat(const std::string& p_name) { return std::get<T>(m_flat[p_name]); }

		/**
		* Interpolate an array of data with the given barycentric coordinates
		*/
		template<typename T>
		void InterpolateData(const std::string& p_key, const std::array<T, 3>& p_data, const glm::vec3& p_barycentricCoords)
		{
			m_interpolatedVarying[p_key] = p_barycentricCoords.x * p_data[0] + p_barycentricCoords.y * p_data[1] + p_barycentricCoords.z * p_data[2];
		}

	private:
		std::unordered_map<std::string, ShaderType> m_uniforms;
		std::unordered_map<std::string, ShaderType> m_varying[3];
		std::unordered_map<std::string, ShaderType> m_interpolatedVarying;
		std::unordered_map<std::string, ShaderType> m_flat;

		uint8_t m_index = 0;
	};
}

#endif // _ASHADER_H