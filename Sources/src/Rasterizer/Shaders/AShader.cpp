/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Shaders/AShader.h"

void Rasterizer::Shaders::AShader::SetUniform(const std::string& p_name, ShaderType p_value)
{
	m_uniforms[p_name] = p_value;
}

void Rasterizer::Shaders::AShader::ClearUniforms()
{
	m_uniforms.clear();
}

void Rasterizer::Shaders::AShader::ClearInternal()
{
	m_internal.clear();
}

void Rasterizer::Shaders::AShader::ClearAll()
{
	ClearUniforms();
	ClearInternal();
}

Rasterizer::Shaders::AShader::ShaderType Rasterizer::Shaders::AShader::GetUniform(const std::string& p_name)
{
	return m_uniforms.at(p_name);
}

Rasterizer::Shaders::AShader::ShaderType Rasterizer::Shaders::AShader::GetInternal(const std::string& p_name)
{
	return m_internal.at(p_name);
}

void Rasterizer::Shaders::AShader::SetInternal(const std::string& p_name, ShaderType p_value)
{
	m_internal[p_name] = p_value;
}
