/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include <glm/geometric.hpp>

#include "Rasterizer/Data/Triangle2D.h"
#include "Rasterizer/Analytics/ProfilerSpy.h"

Rasterizer::Data::Triangle2D::Triangle2D(const Point& p_firstPoint, const Point & p_secondPoint, const Point & p_thirdPoint) :
	m_points { p_firstPoint, p_secondPoint, p_thirdPoint },
	m_area{ CalculateArea() }
{
}

float Rasterizer::Data::Triangle2D::CalculateArea()
{
	return abs
	(
		(
			m_points[0].x * (m_points[1].y - m_points[2].y) +
			m_points[1].x * (m_points[2].y - m_points[0].y) +
			m_points[2].x * (m_points[0].y - m_points[1].y)
		) * 0.5f
	);
}

Rasterizer::Data::Triangle2D::BoundingBox Rasterizer::Data::Triangle2D::GetBoundingBox()
{
	auto result = std::make_tuple
	(
		m_points[0].x > m_points[1].x ? (m_points[0].x > m_points[2].x ? m_points[0].x : m_points[2].x) : (m_points[1].x > m_points[2].x ? m_points[1].x : m_points[2].x),
		m_points[0].y > m_points[1].y ? (m_points[0].y > m_points[2].y ? m_points[0].y : m_points[2].y) : (m_points[1].y > m_points[2].y ? m_points[1].y : m_points[2].y),
		m_points[0].x < m_points[1].x ? (m_points[0].x < m_points[2].x ? m_points[0].x : m_points[2].x) : (m_points[1].x < m_points[2].x ? m_points[1].x : m_points[2].x),
		m_points[0].y < m_points[1].y ? (m_points[0].y < m_points[2].y ? m_points[0].y : m_points[2].y) : (m_points[1].y < m_points[2].y ? m_points[1].y : m_points[2].y)
	);

	if (std::get<0>(result) > std::get<2>(result)) std::swap(std::get<0>(result), std::get<2>(result));
	if (std::get<1>(result) > std::get<3>(result)) std::swap(std::get<1>(result), std::get<3>(result));

	return result;
}

float Rasterizer::Data::Triangle2D::CalculateArea(const Point & p_point1, const Point & p_point2, const Point & p_point3)
{
	return abs
	(
		(
			p_point1.x * (p_point2.y - p_point3.y) +
			p_point2.x * (p_point3.y - p_point1.y) +
			p_point3.x * (p_point1.y - p_point2.y)
			) * 0.5f
	);
}

bool Rasterizer::Data::Triangle2D::IsPointInArea(const Point& p_point)
{
	float A1 = CalculateArea(p_point, m_points[1], m_points[2]);
	float A2 = CalculateArea(m_points[0], p_point, m_points[2]);
	float A3 = CalculateArea(m_points[0], m_points[1], p_point);

	return (m_area == A1 + A2 + A3);
}

bool Rasterizer::Data::Triangle2D::IsPointInPerimeter(const Point& p_point)
{
	glm::vec2 p(p_point.x, p_point.y);

	glm::vec2 a(m_points[0].x, m_points[0].y);
	glm::vec2 b(m_points[1].x, m_points[1].y);
	glm::vec2 c(m_points[2].x, m_points[2].y);

	float ab = sqrtf(static_cast<float>((a - b).length()));
	float ac = sqrtf(static_cast<float>((a - c).length()));
	float bc = sqrtf(static_cast<float>((b - c).length()));
	float ap = sqrtf(static_cast<float>((a - p).length()));
	float bp = sqrtf(static_cast<float>((b - p).length()));
	float cp = sqrtf(static_cast<float>((c - p).length()));

	return ap + bp == ab || bp + cp == bc || cp + ap == ac;
}
