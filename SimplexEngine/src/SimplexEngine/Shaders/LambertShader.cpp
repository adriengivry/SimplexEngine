/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Shaders/LambertShader.h"
#include "SimplexEngine/Materials/DefaultMaterial.h"

using namespace glm;

// Varyings
constexpr int kNormals = 0;

glm::vec4 SimplexEngine::Shaders::LambertShader::VertexModifier(const Data::Vertex & p_vertex)
{
	const mat4 mvp = GetUniform<mat4>(kMVP);
	const mat4 modelMatrix = GetUniform<mat4>(kModel);

	const vec4 vertexWorldPosition = mvp * vec4(p_vertex.position, 1.0f);
	const vec3 vertexNormal = mat3(transpose(inverse(modelMatrix))) * p_vertex.normal;

	SetVarying(kNormals, vertexNormal);

	return vertexWorldPosition;
}

float Lambert(const glm::vec3& p_fragmentNormal, const glm::vec3& p_lightPosition)
{
	const glm::vec3 nrmN = glm::normalize(p_fragmentNormal);
	const glm::vec3 nrmL = glm::normalize(p_lightPosition);
	const float result = glm::dot(nrmN, nrmL);
	return std::max(result, 0.0f);
}

glm::vec4 SimplexEngine::Shaders::LambertShader::FragmentModifier() const
{
	const glm::vec3 lightPosition(5, 10, 5);

	const glm::vec4 diffuse = GetUniform<vec4>(kBaseColor);
	const glm::vec3 normal = GetVarying<vec3>(kNormals);

	return glm::vec4(glm::vec3(diffuse) * Lambert(normal, lightPosition), diffuse.a);
}
