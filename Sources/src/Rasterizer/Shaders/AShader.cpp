/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Shaders/AShader.h"

glm::vec4 Rasterizer::Shaders::AShader::ProcessVertex(const Data::Vertex & p_vertex, uint8_t p_vertexID)
{
	m_index = p_vertexID;
	return VertexModifier(p_vertex);
}

glm::vec3 Rasterizer::Shaders::AShader::ProcessFragment()
{
	glm::vec3 result = FragmentModifier();
	ClearData();
	return result;
}


void Rasterizer::Shaders::AShader::ProcessInterpolation(const glm::vec3& p_barycentricCoords)
{
	m_interpolatedVarying.clear();

	for (const auto&[key, value] : m_varying[0])
	{
		bool isInteger = std::get_if<int>(&m_varying[0][key]) != nullptr;
		bool isFloat = std::get_if<float>(&m_varying[0][key]) != nullptr;
		bool isVec2 = std::get_if<glm::vec2>(&m_varying[0][key]) != nullptr;
		bool isVec3 = std::get_if<glm::vec3>(&m_varying[0][key]) != nullptr;
		bool isVec4 = std::get_if<glm::vec4>(&m_varying[0][key]) != nullptr;
		bool isMat2 = std::get_if<glm::mat2>(&m_varying[0][key]) != nullptr;
		bool isMat3 = std::get_if<glm::mat3>(&m_varying[0][key]) != nullptr;
		bool isMat4 = std::get_if<glm::mat4>(&m_varying[0][key]) != nullptr;

		if (isInteger)
		{
			std::array<int, 3> data{ std::get<int>(m_varying[0][key]), std::get<int>(m_varying[1][key]), std::get<int>(m_varying[2][key]) };
			InterpolateData(key, data, p_barycentricCoords);
		}
		else if (isFloat)
		{
			std::array<float, 3> data{ std::get<float>(m_varying[0][key]), std::get<float>(m_varying[1][key]), std::get<float>(m_varying[2][key]) };
			InterpolateData(key, data, p_barycentricCoords);
		}
		else if (isVec2)
		{
			std::array<glm::vec2, 3> data{ std::get<glm::vec2>(m_varying[0][key]), std::get<glm::vec2>(m_varying[1][key]), std::get<glm::vec2>(m_varying[2][key]) };
			InterpolateData(key, data, p_barycentricCoords);
		}
		else if (isVec3)
		{
			std::array<glm::vec3, 3> data{ std::get<glm::vec3>(m_varying[0][key]), std::get<glm::vec3>(m_varying[1][key]), std::get<glm::vec3>(m_varying[2][key]) };
			InterpolateData(key, data, p_barycentricCoords);
		}
		else if (isVec4)
		{
			std::array<glm::vec4, 3> data{ std::get<glm::vec4>(m_varying[0][key]), std::get<glm::vec4>(m_varying[1][key]), std::get<glm::vec4>(m_varying[2][key]) };
			InterpolateData(key, data, p_barycentricCoords);
		}
		else if (isMat2)
		{
			std::array<glm::mat2, 3> data{ std::get<glm::mat2>(m_varying[0][key]), std::get<glm::mat2>(m_varying[1][key]), std::get<glm::mat2>(m_varying[2][key]) };
			InterpolateData(key, data, p_barycentricCoords);
		}
		else if (isMat3)
		{
			std::array<glm::mat3, 3> data{ std::get<glm::mat3>(m_varying[0][key]), std::get<glm::mat3>(m_varying[1][key]), std::get<glm::mat3>(m_varying[2][key]) };
			InterpolateData(key, data, p_barycentricCoords);
		}
		else if (isMat4)
		{
			std::array<glm::mat4, 3> data{ std::get<glm::mat4>(m_varying[0][key]), std::get<glm::mat4>(m_varying[1][key]), std::get<glm::mat4>(m_varying[2][key]) };
			InterpolateData(key, data, p_barycentricCoords);
		}
	}
}

void Rasterizer::Shaders::AShader::SetUniform(const std::string& p_name, ShaderType p_value)
{
	m_uniforms[p_name] = p_value;
}

void Rasterizer::Shaders::AShader::ClearData()
{
	m_uniforms.clear();
	m_varying[0].clear();
	m_varying[1].clear();
	m_varying[2].clear();
	m_flat.clear();
	m_interpolatedVarying.clear();
}

void Rasterizer::Shaders::AShader::SetVarying(const std::string & p_name, ShaderType p_value)
{
	m_varying[m_index][p_name] = p_value;
}

void Rasterizer::Shaders::AShader::SetFlat(const std::string & p_name, ShaderType p_value)
{
	m_flat[p_name] = p_value;
}