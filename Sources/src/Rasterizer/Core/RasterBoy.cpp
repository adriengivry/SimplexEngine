/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include <iostream>

#include <glm/gtc/matrix_inverse.hpp>

#include "Rasterizer/Core/RasterBoy.h"
#include "Rasterizer/Analytics/ProfilerSpy.h"
#include "Rasterizer/Data/Triangle2D.h"

Rasterizer::Core::RasterBoy::RasterBoy(const Core::Window& p_window, const Entities::Camera& p_camera, Core::Renderer& p_renderer) :
	m_window(p_window),
	m_camera(p_camera),
	m_renderer(p_renderer)
{
}

void Rasterizer::Core::RasterBoy::RasterizeModel(const Entities::Model& p_actor)
{
	glm::mat4 mvp = m_camera.GetViewProjectionMatrix() * p_actor.transform.GetWorldMatrix();

	for (auto mesh : p_actor.GetMeshes())
		RasterizeMesh(mesh.get(), mvp);
}

void Rasterizer::Core::RasterBoy::RasterizeMesh(const Resources::Mesh& p_mesh, const glm::mat4& p_mvp)
{
	auto vertices = p_mesh.GetVertices();
	auto indices = p_mesh.GetIndices();

	/* We add 3 in order to iterate over faces (Made of triangles) */
	for (uint32_t i = 0; i < indices.size(); i += 3)
		RasterizeTriangle(std::make_tuple(vertices[indices[i]], vertices[indices[i + 1]], vertices[indices[i + 2]]), p_mvp);
}

void Rasterizer::Core::RasterBoy::RasterizeTriangle(std::tuple<Data::Vertex, Data::Vertex, Data::Vertex> p_vertices, const glm::mat4 & p_mvp)
{
	auto[v1, depth1] = ProjectToPixelCoordinates(p_mvp * glm::vec4(std::get<0>(p_vertices).position, 1.0f));
	auto[v2, depth2] = ProjectToPixelCoordinates(p_mvp * glm::vec4(std::get<1>(p_vertices).position, 1.0f));
	auto[v3, depth3] = ProjectToPixelCoordinates(p_mvp * glm::vec4(std::get<2>(p_vertices).position, 1.0f));

	if (m_window.IsPointInWindow({ v1.x , v1.y }) || m_window.IsPointInWindow({ v2.x , v2.y }) || m_window.IsPointInWindow({ v3.x , v3.y }))
	{
		/* Calculate face normal by computing the average of the 3 vertices normals */
		glm::vec3 normal1 = std::get<0>(p_vertices).normal;
		glm::vec3 normal2 = std::get<1>(p_vertices).normal;
		glm::vec3 normal3 = std::get<2>(p_vertices).normal;

		glm::vec3 faceNormal = (normal1 + normal2 + normal3) * 0.33f;

		/* Calculate face normal color as a vec3 */
		glm::vec3 faceNormalColorVec = (faceNormal * 0.5f + glm::vec3(0.5f, 0.5f, 0.5f)) * 255.0f;

		/* Converting face normal color to Data::Color */
		Data::Color faceNormalColor(static_cast<uint8_t>(faceNormalColorVec.x), static_cast<uint8_t>(faceNormalColorVec.y), (static_cast<uint8_t>(faceNormalColorVec.z)));

		/* Create a 2D triangle to automate computations (Bouding box, point position check) */
		Data::Triangle2D triangle(v1, v2, v3);

		float verticesAverageDepth = (depth1 + depth2 + depth3) * 0.33f;

		auto[xmin, ymin, xmax, ymax] = triangle.GetBoundingBox();

		for (uint16_t x = xmin; x < xmax && x < m_window.GetWidth(); ++x)
		{
			for (uint16_t y = ymin; y < ymax && y < m_window.GetHeight(); ++y)
			{
				if (triangle.IsPointInArea({ x, y }) && m_window.IsPointInWindow({ x ,y }) && verticesAverageDepth < m_renderer.GetDepth(x, y))
				{
					m_renderer.SetPixel(x, y, faceNormalColor);
					m_renderer.SetDepth(x, y, verticesAverageDepth);
				}
			}
		}
	}
}

std::pair<glm::ivec2, float> Rasterizer::Core::RasterBoy::ProjectToPixelCoordinates(const glm::vec3& p_point)
{
	if (p_point.z <= 0.0f)
		return std::make_pair(glm::ivec2(-1, -1), 0.0f);

	glm::vec2 clipped = p_point / p_point.z;

	glm::ivec2 result;

	result.x = (int)std::round(((clipped.x + 1) * 0.5f) * m_window.GetWidth());
	result.y = (int)std::round(((1 - clipped.y) * 0.5f) * m_window.GetHeight());

	return std::make_pair(result, p_point.z);
}
