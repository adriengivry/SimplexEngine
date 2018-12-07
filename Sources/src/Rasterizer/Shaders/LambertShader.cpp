/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Shaders/LambertShader.h"

glm::vec4 Rasterizer::Shaders::LambertShader::VertexModifier(const Data::Vertex & p_vertex, uint8_t p_vertexID)
{
	glm::mat4 mvp = std::get<glm::mat4>(GetUniform("mvp"));
	glm::mat4 modelMatrix = std::get<glm::mat4>(GetUniform("modelMatrix"));

	glm::vec4 vertexWorldPosition = mvp * glm::vec4(p_vertex.position, 1.0f);
	glm::vec3 vertexNormal = modelMatrix * glm::vec4(p_vertex.normal, 1.0f);

	SetInternal("normals" + std::to_string(p_vertexID + 1), vertexNormal);

	return vertexWorldPosition;
}

glm::vec3 Rasterizer::Shaders::LambertShader::FragmentModifier(const glm::vec3 & p_barycentricCoords)
{
	glm::vec3 normal1 = std::get<glm::vec3>(GetInternal("normals1"));
	glm::vec3 normal2 = std::get<glm::vec3>(GetInternal("normals2"));
	glm::vec3 normal3 = std::get<glm::vec3>(GetInternal("normals3"));

	glm::vec3 normalAverage = p_barycentricCoords.x * normal1 + p_barycentricCoords.y * normal2 + p_barycentricCoords.z * normal3;

	glm::vec3 ambient(0.2f, 0.2f, 0.2f);
	glm::vec3 position(5, 2, 10);
	glm::vec3 diffuse(0.7f, 0.7f, 0.7f);

	return ambient + diffuse * Lambert(normalAverage, position);
}

float Rasterizer::Shaders::LambertShader::Lambert(const glm::vec3 & p_fragmentNormal, const glm::vec3 & p_lightPosition)
{
	glm::vec3 nrmN = glm::normalize(p_fragmentNormal);
	glm::vec3 nrmL = glm::normalize(p_lightPosition);
	float result = glm::dot(nrmN, nrmL);
	return std::max(result, 0.0f);
}
