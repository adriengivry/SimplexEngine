/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include <algorithm>
#include <functional>
#include <iostream>

#include <glm/gtc/matrix_inverse.hpp>

#include <SDL.h>

#include "SimplexEngine/Rendering/Rasterizer.h"
#include "SimplexEngine/Analytics/ProfilerSpy.h"

SimplexEngine::Rendering::Rasterizer::Rasterizer(const Rendering::Renderer& p_renderer, uint16_t p_rasterizationBufferWidth, uint16_t p_rasterizationBufferHeight) :
	m_depthBuffer(p_rasterizationBufferWidth, p_rasterizationBufferHeight),
	m_rasterizationOutputBuffer(p_renderer.GetSDLRenderer(), p_rasterizationBufferWidth, p_rasterizationBufferHeight, SDL_PIXELFORMAT_ABGR32, 1),
	m_rasterizationDrawMode(ERasterizationDrawMode::DEFAULT),
	m_rasterizationCullingMode(ERasterizationCullingMode::BACKFACE),
	m_limitTriangleRasterization(false)
{
}

void SimplexEngine::Rendering::Rasterizer::SetRasterizationDrawMode(ERasterizationDrawMode p_drawMode)
{
	m_rasterizationDrawMode = p_drawMode;
}

SimplexEngine::Rendering::ERasterizationDrawMode SimplexEngine::Rendering::Rasterizer::GetRasterizationDrawMode()
{
	return m_rasterizationDrawMode;
}

void SimplexEngine::Rendering::Rasterizer::SetRasterizationCullingwMode(ERasterizationCullingMode p_cullingMode)
{
	m_rasterizationCullingMode = p_cullingMode;
}

SimplexEngine::Rendering::ERasterizationCullingMode SimplexEngine::Rendering::Rasterizer::GetRasterizationCullingMode()
{
	return m_rasterizationCullingMode;
}

void SimplexEngine::Rendering::Rasterizer::ResetRasterizedTrianglesCount()
{
	m_rasterizedTriangles = 0;
}

void SimplexEngine::Rendering::Rasterizer::ClearBuffers(uint32_t p_clearColor)
{
	m_depthBuffer.Clear();
	m_rasterizationOutputBuffer.Clear(p_clearColor);
}

void SimplexEngine::Rendering::Rasterizer::RasterizeMesh(const Resources::Mesh& p_mesh, Shaders::AShader& p_shader)
{
	auto vertices = p_mesh.GetVertices();
	auto indices = p_mesh.GetIndices();

	/* We add 3 in order to iterate over faces (One triangle is a set of 3 vertices) */
	for (uint32_t i = 0; i < indices.size(); i += 3)
		if (CanRasterize())
			RasterizeTriangle({ vertices[indices[i]], vertices[indices[i + 1]], vertices[indices[i + 2]] }, p_shader);
}

void SimplexEngine::Rendering::Rasterizer::RasterizeTriangle(const std::array<Data::Vertex, 3>& p_vertices, Shaders::AShader& p_shader)
{
	/* Apply the vertex shader to vertices */
	std::array<glm::vec4, 3> transformedVertices = ComputeVertices(p_vertices, p_shader);

	/* Simple Z clipping */
	for (uint8_t i = 0; i < 3; ++i)
	{
		float z = transformedVertices[i].z;
		float w = transformedVertices[i].w;

		if (!((z >= -w && z <= w) && w > 0))
			return;
	}

	/* Convert vertices to raster space (Pixel coordinates) */
	std::for_each(transformedVertices.begin(), transformedVertices.end(), std::bind(&Rasterizer::ConvertToRasterSpace, this, std::placeholders::_1));

	/* Create a 2D triangle to automate computations (Bouding box, point position check) */
	Maths::Triangle2D triangle(transformedVertices[0], transformedVertices[1], transformedVertices[2]);

	if (IsCullingModeSatisfied(triangle))
	{
		switch (m_rasterizationDrawMode)
		{
		case SimplexEngine::Rendering::ERasterizationDrawMode::DEFAULT:
			ComputeFragments(p_shader, transformedVertices, triangle);
			break;
		case SimplexEngine::Rendering::ERasterizationDrawMode::WIREFRAME:
			RasterizeTriangleWireframe(triangle, Data::Color::White);
			break;
		}
	}
}

void SimplexEngine::Rendering::Rasterizer::RasterizeTriangleWireframe(const Maths::Triangle2D & p_triangle, const Data::Color & p_color)
{
	RasterizeLine(p_triangle[0], p_triangle[1], p_color);
	RasterizeLine(p_triangle[1], p_triangle[2], p_color);
	RasterizeLine(p_triangle[2], p_triangle[0], p_color);
}

void SimplexEngine::Rendering::Rasterizer::RasterizeLine(const glm::vec2& p_start, const glm::vec2& p_end, const Data::Color& p_color)
{
	int x0 = (int)p_start.x, y0 = (int)p_start.y, x1 = (int)p_end.x, y1 = (int)p_end.y;
	int dx = abs(x1 - x0), dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1, sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;

	while (true)
	{
		if (x0 >= 0 && x0 < (int)m_rasterizationOutputBuffer.width && y0 >= 0 && y0 < (int)m_rasterizationOutputBuffer.height)
			m_rasterizationOutputBuffer.data[y0 * m_rasterizationOutputBuffer.width + x0] = p_color.Pack();

		if (x0 == x1 && y0 == y1) return;
		int e2 = (err << 1);
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

std::array<glm::vec4, 3> SimplexEngine::Rendering::Rasterizer::ComputeVertices(const std::array<Data::Vertex, 3>& p_vertices, Shaders::AShader& p_shader)
{
	PROFILER_SPY("Rasterizer::ComputeVertices");

	return { p_shader.ProcessVertex(p_vertices[0], 0), p_shader.ProcessVertex(p_vertices[1], 1), p_shader.ProcessVertex(p_vertices[2], 2) };
}

void SimplexEngine::Rendering::Rasterizer::ComputeFragments(Shaders::AShader& p_shader, const std::array<glm::vec4, 3>& p_transformedVertices, Maths::Triangle2D& p_triangle)
{
	PROFILER_SPY("Rasterizer::ComputeFragments");

	/* Very useful to prevent re-calculing things for each fragment */
	p_triangle.PreComputeBarycentric();

	/* Getting bounding box from the triangle to prevent iterating over all the screen */
	auto[xmin, ymin, xmax, ymax] = p_triangle.GetBoundingBox();

	/* Clamp bounding box to window */
	xmin = std::max(0, xmin);
	xmax = std::min(xmax, static_cast<int32_t>(m_rasterizationOutputBuffer.width));
	ymin = std::max(0, ymin);
	ymax = std::min(ymax, static_cast<int32_t>(m_rasterizationOutputBuffer.height));

	/* Here we iterate over the bounding box (Clamped to window size) */
	for (int32_t x = xmin; x < xmax; ++x)
	{
		for (int32_t y = ymin; y < ymax; ++y)
		{
			if (glm::vec3 barycentricCoords = p_triangle.GetBarycentricCoordinates({ x, y }); BarycentricCoordsAreValid(barycentricCoords))
			{
				float depth = CalculatePixelDepth(p_transformedVertices, barycentricCoords);

				if (depth <= m_depthBuffer.GetElement(x, y))
					ComputeFragment({ x, y }, depth, barycentricCoords, p_shader);
			}
		}
	}

	++m_rasterizedTriangles;
}

void SimplexEngine::Rendering::Rasterizer::ComputeFragment(const std::pair<int32_t, int32_t>& p_pixelCoordinates, float p_depth, const glm::vec3& p_barycentricCoordinates, Shaders::AShader & p_shader)
{
	PROFILER_SPY("Rasterizer::ComputeFragment");

	p_shader.ProcessInterpolation(p_barycentricCoordinates);

	uint32_t index = p_pixelCoordinates.second * m_rasterizationOutputBuffer.width + p_pixelCoordinates.first;

	m_rasterizationOutputBuffer.data[index] = p_shader.ProcessFragment().Pack();
	m_depthBuffer.data[index] = p_depth;
}

void SimplexEngine::Rendering::Rasterizer::ConvertToRasterSpace(glm::vec4& p_vertex) const
{
	p_vertex.x /= p_vertex.w;
	p_vertex.y /= p_vertex.w;

	/* Raster Space calculation */
	p_vertex.x = std::round(((p_vertex.x + 1) * 0.5f) * m_rasterizationOutputBuffer.width);
	p_vertex.y = std::round(((1 - p_vertex.y) * 0.5f) * m_rasterizationOutputBuffer.height);
}

bool SimplexEngine::Rendering::Rasterizer::BarycentricCoordsAreValid(const glm::vec3& p_barycentricCoords) const
{
	return p_barycentricCoords.x >= 0.0f && p_barycentricCoords.y >= 0.0f && p_barycentricCoords.x + p_barycentricCoords.y <= 1.0f;
}

float SimplexEngine::Rendering::Rasterizer::CalculatePixelDepth(const std::array<glm::vec4, 3>& p_vertices, const glm::vec3 & p_barycentricCoords) const
{
	return 
		p_vertices[0].z * p_barycentricCoords.z +
		p_vertices[1].z * p_barycentricCoords.y +
		p_vertices[2].z * p_barycentricCoords.x;
}

bool SimplexEngine::Rendering::Rasterizer::IsCullingModeSatisfied(const Maths::Triangle2D & p_triangle)
{
	/* Backface culling (Clock-wise) */

	switch (m_rasterizationCullingMode)
	{
	case ERasterizationCullingMode::DISABLED:	return true;
	case ERasterizationCullingMode::BACKFACE:	return p_triangle.GetArea() < 0.0f;
	case ERasterizationCullingMode::FRONTFACE:	return p_triangle.GetArea() >= 0.0f;
	}

	return true;
}

bool SimplexEngine::Rendering::Rasterizer::CanRasterize() const
{
	return !m_limitTriangleRasterization || m_rasterizedTriangles < m_rasterizedTrianglesLimit;
}

void SimplexEngine::Rendering::Rasterizer::LimitTriangleRasterization(bool p_enable)
{
	m_limitTriangleRasterization = p_enable;
}

void SimplexEngine::Rendering::Rasterizer::SetRasterizedTriangleLimit(uint64_t p_limit)
{
	m_rasterizedTrianglesLimit = p_limit;
}

const SimplexEngine::Buffers::TextureBuffer& SimplexEngine::Rendering::Rasterizer::GetRasterizationOutputBuffer() const
{
	return m_rasterizationOutputBuffer;
}

void SimplexEngine::Rendering::Rasterizer::SendRasterizationOutputBufferToGPU()
{
	m_rasterizationOutputBuffer.SendDataToGPU();
}
