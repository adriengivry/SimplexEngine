/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Shaders/LambertShader.h"

using namespace glm;

glm::vec4 Rasterizer::Shaders::LambertShader::VertexModifier(const Data::Vertex & p_vertex)
{
	mat4 mvp = GetUniform<mat4>("mvp");
	mat4 modelMatrix = GetUniform<mat4>("modelMatrix");

	vec4 vertexWorldPosition = mvp * vec4(p_vertex.position, 1.0f);
	vec3 vertexNormal = mat3(transpose(inverse(modelMatrix))) * p_vertex.normal;

	SetVarying("normal", vertexNormal);

	return vertexWorldPosition;
}

glm::vec3 Rasterizer::Shaders::LambertShader::FragmentModifier()
{
	glm::vec3 ambient(0.05f, 0.05f, 0.05f);
	glm::vec3 position(5, 2, 10);
	glm::vec3 diffuse(0.8f, 0.8f, 0.8f);

	return ambient + diffuse * Lambert(GetVarying<vec3>("normal"), position);
}

float Rasterizer::Shaders::LambertShader::Lambert(const glm::vec3 & p_fragmentNormal, const glm::vec3 & p_lightPosition)
{
	glm::vec3 nrmN = glm::normalize(p_fragmentNormal);
	glm::vec3 nrmL = glm::normalize(p_lightPosition);
	float result = glm::dot(nrmN, nrmL);
	return std::max(result, 0.0f);
}