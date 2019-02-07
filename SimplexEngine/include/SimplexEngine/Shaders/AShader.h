/**
* Project SimplexEngine
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

#include <glm/glm.hpp>

#include "SimplexEngine/API/Export.h"
#include "SimplexEngine/Data/Vertex.h"
#include "SimplexEngine/Data/Color.h"

namespace SimplexEngine::Shaders
{
	/**
	* The AShader class is the base class for any shader of this project.
	* A shader is a simple set of methods that can modify vertices and pixels
	* of the rendering pipeline
	*/
	class API_SIMPLEXENGINE AShader
	{
	public:
		/* A simple typedef for a variant of every types that a shader can use */
		using ShaderValue = std::variant<int, float, glm::vec2, glm::vec3, glm::vec4, glm::mat2, glm::mat3, glm::mat4>;

		/**
		* Process a vertex
		*/
		glm::vec4 ProcessVertex(const SimplexEngine::Data::Vertex& p_vertex, uint8_t p_vertexID);

		/**
		* Process a fragment
		*/
		Data::Color ProcessFragment();

		/**
		* The vertex modifier is where the vertex is modified.
		* It is called before the rasterization stage
		* @param p_vertex
		*/
		virtual glm::vec4 VertexModifier(const SimplexEngine::Data::Vertex& p_vertex) = 0;

		/**
		* The fragment modifier is where every pixels are modified.
		* It is called after the rasterization stage
		*/
		virtual glm::vec4 FragmentModifier() const = 0;

		/**
		* Process interpolation for all varying data and output to fragmentData
		* @param p_barycentricCoords
		*/
		void ProcessInterpolation(const glm::vec3& p_barycentricCoords);

		/**
		* Send a value to the shader (Identified by the given name)
		* to use it in vertex and fragment modifier
		* @param p_name
		* @param p_value
		*/
		void SetUniform(const std::string& p_name, ShaderValue p_value);

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
		T GetUniform(const std::string& p_name) const { return std::get<T>(m_uniforms.at(p_name)); }

		/**
		* Set the varying value identified by the given name to p_value
		* @param p_name
		* @param p_value
		*/
		void SetVarying(const std::string& p_name, ShaderValue p_value);

		/**
		* Set the flat value identified by the given name to p_value
		* @param p_name
		* @param p_value
		*/
		void SetFlat(const std::string& p_name, ShaderValue p_value);

		/**
		* Return the varying value identified by the given name
		* @param p_name
		*/
		template<typename T>
		T GetVarying(const std::string& p_name) const { return std::get<T>(m_interpolatedVarying.at(p_name)); }

		/**
		* Return the flat value identified by the given name
		* @param p_name
		*/
		template<typename T>
		T GetFlat(const std::string& p_name) const { return std::get<T>(m_flat.at(p_name)); }

		/**
		* Interpolate an array of data with the given barycentric coordinates
		* @param p_key (Identifier of where to store the result)
		* @param p_data1
		* @param p_data2
		* @param p_data3
		* @param p_barycentricCoords
		*/
		template<typename T>
		void InterpolateData(const std::string& p_key, const T& p_data1, const T& p_data2, const T& p_data3, const glm::vec3& p_barycentricCoords)
		{
			m_interpolatedVarying[p_key] = 
				p_data1 * p_barycentricCoords.z +
				p_data2 * p_barycentricCoords.y +
				p_data3 * p_barycentricCoords.x;
		}

	private:
		std::unordered_map<std::string, ShaderValue> m_uniforms;
		std::unordered_map<std::string, ShaderValue> m_varying[3];
		std::unordered_map<std::string, ShaderValue> m_interpolatedVarying;
		std::unordered_map<std::string, ShaderValue> m_flat;

		uint8_t m_index = 0;
	};
}

#endif // _ASHADER_H