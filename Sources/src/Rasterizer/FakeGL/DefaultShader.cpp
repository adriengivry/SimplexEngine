/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/FakeGL/DefaultShader.h"

glm::vec4 Rasterizer::FakeGL::DefaultShader::VertexModifier(const Data::Vertex & p_vertex)
{
	glm::vec4 vertexWorldPosition = std::get<glm::mat4>(GetUniform("mvp")) * glm::vec4(p_vertex.position, 1.0f);

	SetInternal("normals", p_vertex.normal);

	return vertexWorldPosition;
}

glm::vec3 Rasterizer::FakeGL::DefaultShader::FragmentModifier(const glm::vec3& p_barycentricCoords)
{
	glm::vec3 normals = std::get<glm::vec3>(GetInternal("normals"));

	glm::vec3 finalColor(normals * 0.5f + glm::vec3(0.5f, 0.5f, 0.5f));

	return finalColor;
}
