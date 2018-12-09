/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include <algorithm>
#include <functional>

#include <glm/gtc/matrix_inverse.hpp>

#include "SimplexEngine/Rendering/Rasterizer.h"
#include "SimplexEngine/Maths/Triangle2D.h"

SimplexEngine::Rendering::Rasterizer::Rasterizer(const Core::Window& p_window, Rendering::Renderer& p_renderer) :
	m_window(p_window),
	m_depthBuffer(m_window.GetWidth(), m_window.GetHeight()),
	m_rasterizationOutputBuffer(p_renderer.GetSDLRenderer(), m_window.GetWidth(), m_window.GetHeight(), SDL_PIXELFORMAT_ABGR32, SDL_TEXTUREACCESS_STREAMING)
{
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
	std::array<glm::vec4, 3> transformedVertex = { p_shader.ProcessVertex(p_vertices[0], 0), p_shader.ProcessVertex(p_vertices[1], 1), p_shader.ProcessVertex(p_vertices[2], 2) };

	/* Convert vertices to raster space (Pixel coordinates) */
	std::for_each(transformedVertex.begin(), transformedVertex.end(), std::bind(&Rasterizer::ConvertToRasterSpace, this, std::placeholders::_1));

	/* Create a 2D triangle to automate computations (Bouding box, point position check) */
	Maths::Triangle2D triangle(transformedVertex[0], transformedVertex[1], transformedVertex[2]);

	/* Very useful to prevent re-calculing things for each fragment */
	triangle.PreComputeBarycentric();

	/* Backface culling (Clock-wise) */
	if (triangle.GetArea() >= 0.0f)
		return;

	/* Getting bounding box from the triangle to prevent iterating over all the screen */
	auto[xmin, ymin, xmax, ymax] = triangle.GetBoundingBox();

	/* Here we iterate over the bounding box (Clamped to window size) */
	for (int32_t x = std::max(0, xmin); x < std::min(xmax, m_window.GetWidthSigned()); ++x)
		for (int32_t y = std::max(0, ymin); y < std::min(ymax, m_window.GetHeightSigned()); ++y)
			if (glm::vec3 barycentricCoords = triangle.GetBarycentricCoordinates({ x, y }); BarycentricCoordsAreValid(barycentricCoords))	/* Is the point in triangle bounds? */
				if (float depth = CalculatePixelDepth(transformedVertex, barycentricCoords); depth <= m_depthBuffer.GetElement(x, y))		/* Is the depth of the point small enough? */
					ComputeFragment({ x, y }, depth, barycentricCoords, p_shader);

	++m_rasterizedTriangles;
}

void SimplexEngine::Rendering::Rasterizer::ComputeFragment(std::pair<int32_t, int32_t> p_pixelCoordinates, float p_depth, const glm::vec3& p_barycentricCoordinates, Shaders::AShader & p_shader)
{
	p_shader.ProcessInterpolation(p_barycentricCoordinates);
	glm::vec3 fragment = p_shader.FragmentModifier() * 255.0f;
	m_rasterizationOutputBuffer.SetPixel(p_pixelCoordinates.first, p_pixelCoordinates.second, { static_cast<uint8_t>(fragment.x), static_cast<uint8_t>(fragment.y), static_cast<uint8_t>(fragment.z) });
	m_depthBuffer.SetElement(p_pixelCoordinates.first, p_pixelCoordinates.second, p_depth);
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
