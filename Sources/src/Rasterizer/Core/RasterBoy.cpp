/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include <iostream>
#include <algorithm>

#include <glm/gtc/matrix_inverse.hpp>

#include "Rasterizer/Core/RasterBoy.h"
#include "Rasterizer/Analytics/ProfilerSpy.h"
#include "Rasterizer/Data/Triangle2D.h"

#include <thread>

Rasterizer::Core::RasterBoy::RasterBoy(const Core::Window& p_window, Core::Renderer& p_renderer) :
	m_window(p_window),
	m_renderer(p_renderer),
	m_depthBuffer(m_window.GetWidth(), m_window.GetHeight()),
	m_rasterizationOutputBuffer(p_renderer.GetSDLRenderer(), m_window.GetWidth(), m_window.GetHeight(), SDL_PIXELFORMAT_ABGR32, SDL_TEXTUREACCESS_STREAMING)
{
}

void Rasterizer::Core::RasterBoy::ResetRasterizedTrianglesCount()
{
	m_rasterizedTriangles = 0;
}

void Rasterizer::Core::RasterBoy::ClearBuffers()
{
	m_depthBuffer.Clear();
	m_rasterizationOutputBuffer.Clear();
}

void Rasterizer::Core::RasterBoy::RasterizeModel(const Entities::Model& p_actor, const Entities::Camera& p_camera)
{
	glm::mat4 mvp = p_camera.GetViewProjectionMatrix() * p_actor.transform.GetWorldMatrix();

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
	if (!CanRasterize())
		return;

	auto[v1, depth1] = ProjectToPixelCoordinates(p_mvp * glm::vec4(std::get<0>(p_vertices).position, 1.0f));
	auto[v2, depth2] = ProjectToPixelCoordinates(p_mvp * glm::vec4(std::get<1>(p_vertices).position, 1.0f));
	auto[v3, depth3] = ProjectToPixelCoordinates(p_mvp * glm::vec4(std::get<2>(p_vertices).position, 1.0f));

	/* Calculate face normal by computing the average of the 3 vertices normals */
	glm::vec3 normal1 = std::get<0>(p_vertices).normal;
	glm::vec3 normal2 = std::get<1>(p_vertices).normal;
	glm::vec3 normal3 = std::get<2>(p_vertices).normal;

	/* Calculate average normal of the face */
	glm::vec3 faceNormal = (normal1 + normal2 + normal3) * 0.33f;

	/* Calculate face normal color as a vec3 */
	glm::vec3 faceNormalColorVec = (faceNormal * 0.5f + glm::vec3(0.5f, 0.5f, 0.5f)) * 255.0f;

	/* Converting face normal color to Data::Color */
	Data::Color faceNormalColor(static_cast<uint8_t>(faceNormalColorVec.x), static_cast<uint8_t>(faceNormalColorVec.y), (static_cast<uint8_t>(faceNormalColorVec.z)));

	/* Create a 2D triangle to automate computations (Bouding box, point position check) */
	Data::Triangle2D triangle(v1, v2, v3);

	/* Getting bounding box from the triangle to prevent iterating over all the screen */
	auto[xmin, ymin, xmax, ymax] = triangle.GetBoundingBox();

	/* Clamp triangle bounds to window size */
	xmin = std::max(0, xmin);
	xmax = std::min(xmax, m_window.GetWidthSigned() - 1);
	ymin = std::max(0, ymin);
	ymax = std::min(ymax, m_window.GetHeightSigned() - 1);

	for (int32_t x = xmin; x < xmax; ++x)
	{
		for (int32_t y = ymin; y < ymax; ++y)
		{
			glm::vec3 bary = triangle.Barycentric({ x, y });
			if (bary.x >= 0.0f && bary.y >= 0.0f && bary.x + bary.y <= 1.0f)
			{
				float depth = depth1 * bary.z + depth2 * bary.x + bary.y * depth3;
				if (depth <= m_depthBuffer.GetElement(x, y))
				{
					m_rasterizationOutputBuffer.SetPixel(x, y, faceNormalColor);
					m_depthBuffer.SetElement(x, y, depth);
				}
			}
	
		}
	}

	++m_rasterizedTriangles;
}

std::pair<glm::vec2, float> Rasterizer::Core::RasterBoy::ProjectToPixelCoordinates(const glm::vec3& p_point)
{
	glm::vec2 clipped = p_point / p_point.z;

	glm::vec2 result;

	result.x = std::round(((clipped.x + 1) * 0.5f) * m_window.GetWidth());
	result.y = std::round(((1 - clipped.y) * 0.5f) * m_window.GetHeight());

	return std::make_pair(result, p_point.z);
}

bool Rasterizer::Core::RasterBoy::CanRasterize()
{
	return !m_limitTriangleRasterization || m_rasterizedTriangles < m_rasterizedTrianglesLimit;
}

void Rasterizer::Core::RasterBoy::LimitTriangleRasterization(bool p_enable)
{
	m_limitTriangleRasterization = p_enable;
}

void Rasterizer::Core::RasterBoy::SetRasterizedTriangleLimit(uint64_t p_limit)
{
	m_rasterizedTrianglesLimit = p_limit;
}

const Rasterizer::Data::Texture & Rasterizer::Core::RasterBoy::GetRasterizationOutputBuffer() const
{
	return m_rasterizationOutputBuffer;
}

void Rasterizer::Core::RasterBoy::SendRasterizationOutputBufferToGPU()
{
	m_rasterizationOutputBuffer.SendDataToGPU();
}
