/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/FakeGL/AShader.h"

void Rasterizer::FakeGL::AShader::SetUniform(const std::string& p_name, ShaderType p_value)
{
	m_uniforms[p_name] = p_value;
}

void Rasterizer::FakeGL::AShader::ClearUniforms()
{
	m_uniforms.clear();
}

void Rasterizer::FakeGL::AShader::ClearInternal()
{
	m_internal.clear();
}

void Rasterizer::FakeGL::AShader::ClearAll()
{
	ClearUniforms();
	ClearInternal();
}

Rasterizer::FakeGL::AShader::ShaderType Rasterizer::FakeGL::AShader::GetUniform(const std::string& p_name)
{
	return m_uniforms.at(p_name);
}

Rasterizer::FakeGL::AShader::ShaderType Rasterizer::FakeGL::AShader::GetInternal(const std::string& p_name)
{
	return m_internal.at(p_name);
}

void Rasterizer::FakeGL::AShader::SetInternal(const std::string& p_name, ShaderType p_value)
{
	m_internal[p_name] = p_value;
}
