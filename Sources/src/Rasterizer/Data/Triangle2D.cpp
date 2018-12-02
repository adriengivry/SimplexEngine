/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include <glm/geometric.hpp>

#include "Rasterizer/Data/Triangle2D.h"

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
			m_points[0].first * (m_points[1].second - m_points[2].second) +
			m_points[1].first * (m_points[2].second - m_points[0].second) +
			m_points[2].first * (m_points[0].second - m_points[1].second)
		) * 0.5f
	);
}

Rasterizer::Data::Triangle2D::BoundingBox Rasterizer::Data::Triangle2D::GetBoundingBox()
{
	return std::make_tuple
	(
		m_points[0].first > m_points[1].first ? (m_points[0].first > m_points[2].first ? m_points[0].first : m_points[2].first) : (m_points[1].first > m_points[2].first ? m_points[1].first : m_points[2].first),
		m_points[0].second > m_points[1].second ? (m_points[0].second > m_points[2].second ? m_points[0].second : m_points[2].second) : (m_points[1].second > m_points[2].second ? m_points[1].second : m_points[2].second),
		m_points[0].first < m_points[1].first ? (m_points[0].first < m_points[2].first ? m_points[0].first : m_points[2].first) : (m_points[1].first < m_points[2].first ? m_points[1].first : m_points[2].first),
		m_points[0].second < m_points[1].second ? (m_points[0].second < m_points[2].second ? m_points[0].second : m_points[2].second) : (m_points[1].second < m_points[2].second ? m_points[1].second : m_points[2].second)
	);
}

float Rasterizer::Data::Triangle2D::CalculateArea(const Point & p_point1, const Point & p_point2, const Point & p_point3)
{
	return abs
	(
		(
			p_point1.first * (p_point2.second - p_point3.second) +
			p_point2.first * (p_point3.second - p_point1.second) +
			p_point3.first * (p_point1.second - p_point2.second)
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
	glm::vec2 p(p_point.first, p_point.second);

	glm::vec2 a(m_points[0].first, m_points[0].second);
	glm::vec2 b(m_points[1].first, m_points[1].second);
	glm::vec2 c(m_points[2].first, m_points[2].second);

	float ab = sqrtf(static_cast<float>((a - b).length()));
	float ac = sqrtf(static_cast<float>((a - c).length()));
	float bc = sqrtf(static_cast<float>((b - c).length()));
	float ap = sqrtf(static_cast<float>((a - p).length()));
	float bp = sqrtf(static_cast<float>((b - p).length()));
	float cp = sqrtf(static_cast<float>((c - p).length()));

	return ap + bp == ab || bp + cp == bc || cp + ap == ac;
}
