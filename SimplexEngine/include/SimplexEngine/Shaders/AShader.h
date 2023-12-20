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
		* Send a value to the shader (Identified by the given index)
		* to use it in vertex and fragment modifier
		* @param p_index
		* @param p_value
		*/
        template<typename T>
        void SetUniform(uint8_t p_index, T p_value) { reinterpret_cast<T&>(m_uniforms[p_index]) = p_value; }

		/**
		* Clear any data stored in this shader
		*/
		void ClearData();

	protected:
		/**
		* Return the value of the uniform identified by the given index
		* @param p_index
		*/
		template<typename T>
		T GetUniform(uint8_t p_index) const { return reinterpret_cast<const T&>(m_uniforms[p_index]); }

		/**
		* Set the varying value identified by the given index to p_value
		* @param p_index
		* @param p_value
		*/
        template<typename T>
        void SetVarying(uint8_t p_index, T p_value)
        {
            m_lastVaryingIndex = p_index + 1;
            reinterpret_cast<T&>(m_varying[p_index][m_index]) = p_value;
        }

		/**
		* Set the flat value identified by the given index
		* @param uint8_t
		* @param p_value
		*/
        template<typename T>
        void SetFlat(uint8_t p_index, T p_value)  { reinterpret_cast<T&>(m_flat[p_index]) = p_value; }

		/**
		* Return the varying value identified by the given index
		* @param p_index
		*/
		template<typename T>
		T GetVarying(uint8_t p_index) const { return reinterpret_cast<const T&>(m_interpolatedVarying[p_index]); }

		/**
		* Return the flat value identified by the given index
		* @param p_index
		*/
		template<typename T>
        T GetFlat(uint8_t p_index) const { return reinterpret_cast<const T&>(m_flat[p_index] ); }

	private:
		glm::mat4 m_uniforms[256];
		glm::vec4 m_flat[256];
		glm::vec4 m_varying[256][3];
		glm::vec4 m_interpolatedVarying[256];
        uint8_t m_lastVaryingIndex = 0;
		uint8_t m_index = 0;
	};
}

#endif // _ASHADER_H