/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Shaders/DefaultShader.h"

glm::vec4 Rasterizer::Shaders::DefaultShader::VertexModifier(const Data::Vertex& p_vertex, uint8_t p_vertexID)
{
	glm::mat4 mvp = std::get<glm::mat4>(GetUniform("mvp"));

	glm::vec4 vertexWorldPosition = mvp * glm::vec4(p_vertex.position, 1.0f);

	SetInternal("normals" + std::to_string(p_vertexID + 1), p_vertex.normal);

	return vertexWorldPosition;
}

glm::vec3 Rasterizer::Shaders::DefaultShader::FragmentModifier(const glm::vec3& p_barycentricCoords)
{
	glm::vec3 normal1 = std::get<glm::vec3>(GetInternal("normals1"));
	glm::vec3 normal2 = std::get<glm::vec3>(GetInternal("normals2"));
	glm::vec3 normal3 = std::get<glm::vec3>(GetInternal("normals3"));

	glm::vec3 normalAverage = p_barycentricCoords.x * normal1 + p_barycentricCoords.y * normal2 + p_barycentricCoords.z * normal3;

	glm::vec3 finalColor(normalAverage * 0.5f + glm::vec3(0.5f, 0.5f, 0.5f));
	return finalColor;
}
