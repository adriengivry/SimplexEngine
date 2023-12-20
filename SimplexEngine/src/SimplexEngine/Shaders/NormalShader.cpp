/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Shaders/NormalShader.h"
#include "SimplexEngine/Materials/DefaultMaterial.h"

using namespace glm;

// Varyings
constexpr int NORMALS = 0;

glm::vec4 SimplexEngine::Shaders::NormalShader::VertexModifier(const Data::Vertex& p_vertex)
{
	mat4 mvp = GetUniform<mat4>(MVP);
	mat4 modelMatrix = GetUniform<mat4>(MODEL_MATRIX);

	vec4 vertexWorldPosition = mvp * vec4(p_vertex.position, 1.0f);

	vec3 normal = mat3(transpose(inverse(modelMatrix))) * p_vertex.normal;

	SetVarying(NORMALS, normal);

	return vertexWorldPosition;
}

glm::vec4 SimplexEngine::Shaders::NormalShader::FragmentModifier() const
{
	vec3 normal = normalize(GetVarying<vec3>(NORMALS));

	return vec4(normal * 0.5f + glm::vec3(0.5f, 0.5f, 0.5f), 1.0f);
}
