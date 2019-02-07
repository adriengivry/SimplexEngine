/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Shaders/LambertShader.h"

using namespace glm;

glm::vec4 SimplexEngine::Shaders::LambertShader::VertexModifier(const Data::Vertex & p_vertex)
{
	mat4 mvp = GetUniform<mat4>("mvp");
	mat4 modelMatrix = GetUniform<mat4>("modelMatrix");

	vec4 vertexWorldPosition = mvp * vec4(p_vertex.position, 1.0f);
	vec3 vertexNormal = mat3(transpose(inverse(modelMatrix))) * p_vertex.normal;

	SetVarying("normal", vertexNormal);

	return vertexWorldPosition;
}

glm::vec4 SimplexEngine::Shaders::LambertShader::FragmentModifier() const
{
	glm::vec3 lightPosition(5, 10, 5);

	glm::vec4 diffuse = GetUniform<vec4>("baseColor");
	glm::vec3 normal = GetVarying<vec3>("normal");

	return diffuse * Lambert(normal, lightPosition);
}

float SimplexEngine::Shaders::LambertShader::Lambert(const glm::vec3 & p_fragmentNormal, const glm::vec3 & p_lightPosition) const
{
	glm::vec3 nrmN = glm::normalize(p_fragmentNormal);
	glm::vec3 nrmL = glm::normalize(p_lightPosition);
	float result = glm::dot(nrmN, nrmL);
	return std::max(result, 0.0f);
}
