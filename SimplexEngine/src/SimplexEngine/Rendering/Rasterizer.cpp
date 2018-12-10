/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include <algorithm>
#include <functional>

#include <glm/gtc/matrix_inverse.hpp>

#include <SDL.h>

#include "SimplexEngine/Rendering/Rasterizer.h"
#include "SimplexEngine/Analytics/ProfilerSpy.h"

SimplexEngine::Rendering::Rasterizer::Rasterizer(const Windowing::Window& p_window, Rendering::Renderer& p_renderer) :
	m_window(p_window),
	m_depthBuffer(m_window.GetWidth(), m_window.GetHeight()),
	m_rasterizationOutputBuffer(p_renderer.GetSDLRenderer(), m_window.GetWidth(), m_window.GetHeight(), SDL_PIXELFORMAT_ABGR32, 1),
	m_rasterizationMode(ERasterizationMode::DEFAULT)
{
}

void SimplexEngine::Rendering::Rasterizer::SetRasterizationMode(ERasterizationMode p_newMode)
{
	m_rasterizationMode = p_newMode;
}

SimplexEngine::Rendering::ERasterizationMode SimplexEngine::Rendering::Rasterizer::GetRasterizationMode()
{
	return m_rasterizationMode;
}

void SimplexEngine::Rendering::Rasterizer::ResetRasterizedTrianglesCount()
{
	m_rasterizedTriangles = 0;
}

void SimplexEngine::Rendering::Rasterizer::ClearBuffers()
{
	m_depthBuffer.Clear();
	m_rasterizationOutputBuffer.Clear();
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

	/* Convert vertices to raster space (Pixel coordinates) */
	std::for_each(transformedVertices.begin(), transformedVertices.end(), std::bind(&Rasterizer::ConvertToRasterSpace, this, std::placeholders::_1));

	if (m_rasterizationMode == ERasterizationMode::WIREFRAME)
	{
		/* Draw the triangle in wireframe mode (No shader computation) */
		RasterizeLine(transformedVertices[0], transformedVertices[1], Data::Color::Red);
		RasterizeLine(transformedVertices[1], transformedVertices[2], Data::Color::Red);
		RasterizeLine(transformedVertices[2], transformedVertices[0], Data::Color::Red);
	}
	else
	{
		/* Create a 2D triangle to automate computations (Bouding box, point position check) */
		Maths::Triangle2D triangle(transformedVertices[0], transformedVertices[1], transformedVertices[2]);

		/* Backface culling (Clock-wise) */
		if (triangle.GetArea() < 0.0f)
			ComputeFragments(p_shader, transformedVertices, triangle);
	}
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
	xmax = std::min(xmax, m_window.GetWidthSigned());
	ymin = std::max(0, ymin);
	ymax = std::min(ymax, m_window.GetHeightSigned());

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
	/* Homogenize */
	p_vertex /= p_vertex.w;

	/* Raster Space calculation */
	p_vertex.x = std::round(((p_vertex.x + 1) * 0.5f) * m_window.GetWidth());
	p_vertex.y = std::round(((1 - p_vertex.y) * 0.5f) * m_window.GetHeight());
}

bool SimplexEngine::Rendering::Rasterizer::BarycentricCoordsAreValid(const glm::vec3& p_barycentricCoords) const
{
	return p_barycentricCoords.x >= 0.0f && p_barycentricCoords.y >= 0.0f && p_barycentricCoords.x + p_barycentricCoords.y <= 1.0f;
}

float SimplexEngine::Rendering::Rasterizer::CalculatePixelDepth(const std::array<glm::vec4, 3>& p_vertices, const glm::vec3 & p_barycentricCoords) const
{
	return p_vertices[0].z * p_barycentricCoords.z + p_vertices[2].z * p_barycentricCoords.x + p_barycentricCoords.y * p_vertices[1].z;
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
