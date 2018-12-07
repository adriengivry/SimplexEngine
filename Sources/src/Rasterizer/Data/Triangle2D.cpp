/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include <glm/geometric.hpp>

#include "Rasterizer/Data/Triangle2D.h"

Rasterizer::Data::Triangle2D::Triangle2D(const glm::vec2& p_vertex1, const glm::vec2& p_vertex2, const glm::vec2& p_vertex3) : m_vertices{ p_vertex1, p_vertex2, p_vertex3 } {}

void Rasterizer::Data::Triangle2D::PreComputeBarycentric()
{
	m_V0 = glm::vec2(m_vertices[2].x - m_vertices[0].x, m_vertices[2].y - m_vertices[0].y);
	m_V1 = glm::vec2(m_vertices[1].x - m_vertices[0].x, m_vertices[1].y - m_vertices[0].y);
	m_d00 = m_V0.x * m_V0.x + m_V0.y * m_V0.y;
	m_d01 = m_V0.x * m_V1.x + m_V0.y * m_V1.y;
	m_d10 = m_V1.x * m_V0.x + m_V1.y * m_V1.y;
	m_d11 = m_V1.x * m_V1.x + m_V1.y * m_V1.y;
	m_Denom = 1.0f / (m_d00 * m_d11 - m_d01 * m_d01);
}

float Rasterizer::Data::Triangle2D::GetArea() const
{
	glm::vec2 v(m_vertices[1].x - m_vertices[0].x, m_vertices[1].y - m_vertices[0].y);
	glm::vec2 w(m_vertices[2].x - m_vertices[0].x, m_vertices[2].y - m_vertices[0].y);
	return (v.x * w.y - v.y * w.x);
}

Rasterizer::Data::Triangle2D::BoundingBox Rasterizer::Data::Triangle2D::GetBoundingBox() const
{
	BoundingBox result = std::make_tuple
	(
		static_cast<int32_t>(m_vertices[0].x > m_vertices[1].x ? (m_vertices[0].x > m_vertices[2].x ? m_vertices[0].x : m_vertices[2].x) : (m_vertices[1].x > m_vertices[2].x ? m_vertices[1].x : m_vertices[2].x)),
		static_cast<int32_t>(m_vertices[0].y > m_vertices[1].y ? (m_vertices[0].y > m_vertices[2].y ? m_vertices[0].y : m_vertices[2].y) : (m_vertices[1].y > m_vertices[2].y ? m_vertices[1].y : m_vertices[2].y)),
		static_cast<int32_t>(m_vertices[0].x < m_vertices[1].x ? (m_vertices[0].x < m_vertices[2].x ? m_vertices[0].x : m_vertices[2].x) : (m_vertices[1].x < m_vertices[2].x ? m_vertices[1].x : m_vertices[2].x)),
		static_cast<int32_t>(m_vertices[0].y < m_vertices[1].y ? (m_vertices[0].y < m_vertices[2].y ? m_vertices[0].y : m_vertices[2].y) : (m_vertices[1].y < m_vertices[2].y ? m_vertices[1].y : m_vertices[2].y))
	);

	if (std::get<0>(result) > std::get<2>(result)) std::swap(std::get<0>(result), std::get<2>(result));
	if (std::get<1>(result) > std::get<3>(result)) std::swap(std::get<1>(result), std::get<3>(result));

	return result;
}

glm::vec3 Rasterizer::Data::Triangle2D::GetBarycentricCoordinates(const glm::vec2& p_point, uint8_t p_referenceVertex) const
{
	const float x = p_point.x - m_vertices[p_referenceVertex].x;
	const float y = p_point.y - m_vertices[p_referenceVertex].y;

	const float d02 = m_V0.x * x + m_V0.y * y;
	const float d12 = m_V1.x * x + m_V1.y * y;
	const float v = (m_d11 * d02 - m_d01 * d12) * m_Denom;
	const float u = (m_d00 * d12 - m_d01 * d02) * m_Denom;

	return glm::vec3(v, u, 1.0f - v - u);
}