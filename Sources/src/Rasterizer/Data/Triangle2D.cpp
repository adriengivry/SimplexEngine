/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include <glm/geometric.hpp>

#include "Rasterizer/Data/Triangle2D.h"
#include "Rasterizer/Analytics/ProfilerSpy.h"

Rasterizer::Data::Triangle2D::Triangle2D(const Point& p_firstPoint, const Point & p_secondPoint, const Point & p_thirdPoint) :
	m_points { p_firstPoint, p_secondPoint, p_thirdPoint }
{
	UpdateBarycentric();
}

float Rasterizer::Data::Triangle2D::CalculateArea()
{
	glm::vec2 v(m_points[1].x - m_points[0].x, m_points[1].y - m_points[0].y);
	glm::vec2 w(m_points[2].x - m_points[0].x, m_points[2].y - m_points[0].y);
	return (v.x * w.y - v.y * w.x);
}

void Rasterizer::Data::Triangle2D::UpdateBarycentric()
{
	m_V0 = glm::vec2(m_points[2].x - m_points[0].x, m_points[2].y - m_points[0].y);
	m_V1 = glm::vec2(m_points[1].x - m_points[0].x, m_points[1].y - m_points[0].y);
	m_d00 = m_V0.x * m_V0.x + m_V0.y * m_V0.y;
	m_d01 = m_V0.x * m_V1.x + m_V0.y * m_V1.y;
	m_d10 = m_V1.x * m_V0.x + m_V1.y * m_V1.y;
	m_d11 = m_V1.x * m_V1.x + m_V1.y * m_V1.y;
	m_Denom = 1.0f / (m_d00 * m_d11 - m_d01 * m_d01);
}

Rasterizer::Data::Triangle2D::BoundingBox Rasterizer::Data::Triangle2D::GetBoundingBox()
{
	BoundingBox result = std::make_tuple
	(
		static_cast<int32_t>(m_points[0].x > m_points[1].x ? (m_points[0].x > m_points[2].x ? m_points[0].x : m_points[2].x) : (m_points[1].x > m_points[2].x ? m_points[1].x : m_points[2].x)),
		static_cast<int32_t>(m_points[0].y > m_points[1].y ? (m_points[0].y > m_points[2].y ? m_points[0].y : m_points[2].y) : (m_points[1].y > m_points[2].y ? m_points[1].y : m_points[2].y)),
		static_cast<int32_t>(m_points[0].x < m_points[1].x ? (m_points[0].x < m_points[2].x ? m_points[0].x : m_points[2].x) : (m_points[1].x < m_points[2].x ? m_points[1].x : m_points[2].x)),
		static_cast<int32_t>(m_points[0].y < m_points[1].y ? (m_points[0].y < m_points[2].y ? m_points[0].y : m_points[2].y) : (m_points[1].y < m_points[2].y ? m_points[1].y : m_points[2].y))
	);

	if (std::get<0>(result) > std::get<2>(result)) std::swap(std::get<0>(result), std::get<2>(result));
	if (std::get<1>(result) > std::get<3>(result)) std::swap(std::get<1>(result), std::get<3>(result));

	return result;
}

glm::vec3 Rasterizer::Data::Triangle2D::Barycentric(const Point& p_point)
{
	const float x = p_point.x - m_points[0].x;
	const float y = p_point.y - m_points[0].y;

	const float d02 = m_V0.x * x + m_V0.y * y;
	const float d12 = m_V1.x * x + m_V1.y * y;
	const float v = (m_d11 * d02 - m_d01 * d12) * m_Denom;
	const float u = (m_d00 * d12 - m_d01 * d02) * m_Denom;

	return glm::vec3(v, u, 1.0f - v - u);
}