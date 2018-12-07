/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Shaders/DefaultShader.h"

using namespace glm;

glm::vec4 Rasterizer::Shaders::DefaultShader::VertexModifier(const Data::Vertex& p_vertex)
{
	mat4 mvp = GetUniform<mat4>("mvp");
	mat4 modelMatrix = GetUniform<mat4>("modelMatrix");

	vec4 vertexWorldPosition = mvp * vec4(p_vertex.position, 1.0f);

	vec3 normal = mat3(transpose(inverse(modelMatrix))) * p_vertex.normal;

	SetVarying("normal", normal);

	return vertexWorldPosition;
}

glm::vec3 Rasterizer::Shaders::DefaultShader::FragmentModifier()
{
	vec3 normal = normalize(GetVarying<vec3>("normal"));

	vec3 finalColor(normal * 0.5f + glm::vec3(0.5f, 0.5f, 0.5f));

	return finalColor;
}
