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

void Rasterizer::Core::RasterBoy::RasterizeModel(const Entities::Model& p_actor, Shaders::AShader& p_shader)
{
	for (auto mesh : p_actor.GetMeshes())
		RasterizeMesh(mesh.get(), p_shader);
}

void Rasterizer::Core::RasterBoy::RasterizeMesh(const Resources::Mesh& p_mesh, Shaders::AShader& p_shader)
{
	auto vertices = p_mesh.GetVertices();
	auto indices = p_mesh.GetIndices();

	/* We add 3 in order to iterate over faces (One triangle is a set of 3 vertices) */
	for (uint32_t i = 0; i < indices.size(); i += 3)
		RasterizeTriangle({ vertices[indices[i]], vertices[indices[i + 1]], vertices[indices[i + 2]] }, p_shader);
}

void Rasterizer::Core::RasterBoy::RasterizeTriangle(const std::array<Data::Vertex, 3>& p_vertices, Shaders::AShader& p_shader)
{
	if (!CanRasterize())
		return;

	std::array<glm::vec4, 3> transformedVertex = { p_shader.ProcessVertex(p_vertices[0], 0), p_shader.ProcessVertex(p_vertices[1], 1), p_shader.ProcessVertex(p_vertices[2], 2) };

	std::for_each(transformedVertex.begin(), transformedVertex.end(), std::bind(&RasterBoy::ConvertToRasterSpace, this, std::placeholders::_1));

	/* Create a 2D triangle to automate computations (Bouding box, point position check) */
	Data::Triangle2D triangle(transformedVertex[0], transformedVertex[1], transformedVertex[2]);

	triangle.PreComputeBarycentric();

	/* Backface culling (Clock-wise) */
	if (triangle.GetArea() >= 0.0f)
		return;

	/* Getting bounding box from the triangle to prevent iterating over all the screen */
	auto[xmin, ymin, xmax, ymax] = triangle.GetBoundingBox();

	/* Here we iterate over the bounding box (Clamped to window size) */
	for (int32_t x = std::max(0, xmin); x < std::min(xmax, m_window.GetWidthSigned()); ++x)
	{
		for (int32_t y = std::max(0, ymin); y < std::min(ymax, m_window.GetHeightSigned()); ++y)
		{
			glm::vec3 barycentricCoords = triangle.GetBarycentricCoordinates({ x, y });

			if (barycentricCoords.x >= 0.0f && barycentricCoords.y >= 0.0f && barycentricCoords.x + barycentricCoords.y <= 1.0f)
			{
				float depth = transformedVertex[0].z * barycentricCoords.z + transformedVertex[2].z * barycentricCoords.x + barycentricCoords.y * transformedVertex[1].z;

				if (depth <= m_depthBuffer.GetElement(x, y))
				{
					p_shader.ProcessInterpolation(barycentricCoords);
					glm::vec3 fragment = p_shader.FragmentModifier() * 255.0f;
					m_rasterizationOutputBuffer.SetPixel(x, y, { static_cast<uint8_t>(fragment.x), static_cast<uint8_t>(fragment.y), static_cast<uint8_t>(fragment.z) });
					m_depthBuffer.SetElement(x, y, depth);
				}
			}
	
		}
	}

	++m_rasterizedTriangles;
}

void Rasterizer::Core::RasterBoy::ConvertToRasterSpace(glm::vec4& p_vertex)
{
	/* Homogenize */
	p_vertex /= p_vertex.w;

	/* Raster Space calculation */
	p_vertex.x = std::round(((p_vertex.x + 1) * 0.5f) * m_window.GetWidth());
	p_vertex.y = std::round(((1 - p_vertex.y) * 0.5f) * m_window.GetHeight());
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
