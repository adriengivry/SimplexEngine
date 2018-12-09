/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Shaders/AShader.h"
#include "SimplexEngine/Analytics/ProfilerSpy.h"

glm::vec4 SimplexEngine::Shaders::AShader::ProcessVertex(const Data::Vertex & p_vertex, uint8_t p_vertexID)
{
	m_index = p_vertexID;
	return VertexModifier(p_vertex);
}

glm::vec3 SimplexEngine::Shaders::AShader::ProcessFragment()
{
	PROFILER_SPY("AShader::ProcessFragment");

	glm::vec3 result = FragmentModifier();
	ClearData();
	return result;
}

void SimplexEngine::Shaders::AShader::ProcessInterpolation(const glm::vec3 & p_barycentricCoords)
{
	PROFILER_SPY("AShader::ProcessInterpolation");

	for (const auto&[key, value] : m_varying[0])
	{
		if (std::get_if<glm::vec3>(&m_varying[0][key]))
		{
			InterpolateData(key, std::get<glm::vec3>(m_varying[0][key]), std::get<glm::vec3>(m_varying[0][key]), std::get<glm::vec3>(m_varying[0][key]), p_barycentricCoords);
		}
		else if (std::get_if<glm::vec4>(&m_varying[0][key]))
		{
			InterpolateData(key, std::get<glm::vec4>(m_varying[0][key]), std::get<glm::vec4>(m_varying[0][key]), std::get<glm::vec4>(m_varying[0][key]), p_barycentricCoords);
		}
		else if (std::get_if<float>(&m_varying[0][key]))
		{
			InterpolateData(key, std::get<float>(m_varying[0][key]), std::get<float>(m_varying[0][key]), std::get<float>(m_varying[0][key]), p_barycentricCoords);
		}
		else if (std::get_if<glm::vec2>(&m_varying[0][key]))
		{
			InterpolateData(key, std::get<glm::vec2>(m_varying[0][key]), std::get<glm::vec2>(m_varying[0][key]), std::get<glm::vec2>(m_varying[0][key]), p_barycentricCoords);
		}
		else if (std::get_if<int>(&m_varying[0][key]))
		{
			InterpolateData(key, std::get<int>(m_varying[0][key]), std::get<int>(m_varying[0][key]), std::get<int>(m_varying[0][key]), p_barycentricCoords);
		}
		else if (std::get_if<glm::mat3>(&m_varying[0][key]))
		{
			InterpolateData(key, std::get<glm::mat3>(m_varying[0][key]), std::get<glm::mat3>(m_varying[0][key]), std::get<glm::mat3>(m_varying[0][key]), p_barycentricCoords);
		}
		else if (std::get_if<glm::mat4>(&m_varying[0][key]))
		{
			InterpolateData(key, std::get<glm::mat4>(m_varying[0][key]), std::get<glm::mat4>(m_varying[0][key]), std::get<glm::mat4>(m_varying[0][key]), p_barycentricCoords);
		}
		else if (std::get_if<glm::mat2>(&m_varying[0][key]))
		{
			InterpolateData(key, std::get<glm::mat2>(m_varying[0][key]), std::get<glm::mat2>(m_varying[0][key]), std::get<glm::mat2>(m_varying[0][key]), p_barycentricCoords);
		}
	}
}

void SimplexEngine::Shaders::AShader::SetUniform(const std::string& p_name, ShaderValue p_value)
{
	m_uniforms[p_name] = p_value;
}

void SimplexEngine::Shaders::AShader::ClearData()
{
	PROFILER_SPY("AShader::ClearData");

	m_uniforms.clear();
	m_varying[0].clear();
	m_varying[1].clear();
	m_varying[2].clear();
	m_flat.clear();
	m_interpolatedVarying.clear();
}

void SimplexEngine::Shaders::AShader::SetVarying(const std::string & p_name, ShaderValue p_value)
{
	m_varying[m_index][p_name] = p_value;
}

void SimplexEngine::Shaders::AShader::SetFlat(const std::string & p_name, ShaderValue p_value)
{
	m_flat[p_name] = p_value;
}