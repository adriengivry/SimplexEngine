/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Data/Triangle2D.h"

Rasterizer::Data::Triangle2D::Triangle2D(const Entities::Camera& p_camera, const AltMath::Matrix4f& p_verticesTransformation, const const Data::Vertex & p_firstVertex, const Data::Vertex & p_secondVertex, const Data::Vertex & p_thirdVertex)
{
	AltMath::Matrix4f mvp = p_camera.GetViewProjectionMatrix() * p_verticesTransformation;

	auto toScreen = [](const AltMath::Vector4f& p_vector, float p_width, float p_height)
	{
		const float widthHalf = p_width / 2.0f;
		const float heightHalf = p_height / 2.0f;
		return AltMath::Vector2i(static_cast<int>(((p_vector.x / 5.0f) + 1) * widthHalf), static_cast<int>(p_height - ((p_vector.y / 5.0f) + 1) * heightHalf));
	};

	m_points[0] = toScreen(mvp * AltMath::Vector4f(p_firstVertex.position), 1280, 720);
	m_points[1] = toScreen(mvp * AltMath::Vector4f(p_secondVertex.position), 1280, 720);
	m_points[2] = toScreen(mvp * AltMath::Vector4f(p_thirdVertex.position), 1280, 720);

	m_area = CalculateArea();
}

Rasterizer::Data::Triangle2D::Triangle2D(const AltMath::Vector2i & p_firstPoint, const AltMath::Vector2i & p_secondPoint, const AltMath::Vector2i & p_thirdPoint) :
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

float Rasterizer::Data::Triangle2D::CalculateArea(const AltMath::Vector2i & p_point1, const AltMath::Vector2i & p_point2, const AltMath::Vector2i & p_point3)
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

bool Rasterizer::Data::Triangle2D::IsPointIn(const AltMath::Vector2i& p_point)
{
	float A1 = CalculateArea(p_point, m_points[1], m_points[2]);
	float A2 = CalculateArea(m_points[0], p_point, m_points[2]);
	float A3 = CalculateArea(m_points[0], m_points[1], p_point);

	return (m_area == A1 + A2 + A3);
}
