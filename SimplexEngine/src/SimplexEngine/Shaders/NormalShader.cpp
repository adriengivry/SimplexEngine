/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Shaders/NormalShader.h"

using namespace glm;

glm::vec4 SimplexEngine::Shaders::NormalShader::VertexModifier(const Data::Vertex& p_vertex)
{
	mat4 mvp = GetUniform<mat4>("mvp");
	mat4 modelMatrix = GetUniform<mat4>("modelMatrix");

	vec4 vertexWorldPosition = mvp * vec4(p_vertex.position, 1.0f);

	vec3 normal = mat3(transpose(inverse(modelMatrix))) * p_vertex.normal;

	SetVarying("normal", normal);

	return vertexWorldPosition;
}

glm::vec4 SimplexEngine::Shaders::NormalShader::FragmentModifier() const
{
	vec3 normal = normalize(GetVarying<vec3>("normal"));

	return vec4(normal * 0.5f + glm::vec3(0.5f, 0.5f, 0.5f), 1.0f);
}
