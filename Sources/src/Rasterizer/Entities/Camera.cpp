/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include <glm/gtc/matrix_transform.hpp>

#include "Rasterizer/Entities/Camera.h"

Rasterizer::Entities::Camera::Camera(const glm::vec3 & p_position, const glm::vec3& p_lookAt, const glm::vec3 & p_upVector, uint32_t p_windowWidth, uint32_t p_windowHeight, float p_fov, float p_near, float p_far) :
	AEntity(p_position),
	m_lookAt(p_lookAt),
	m_upVector(p_upVector),
	m_windowWidth(p_windowWidth),
	m_windowHeight(p_windowHeight),
	m_windowHalfWidth(p_windowWidth * 0.5f),
	m_windowHalfHeight(p_windowHeight * 0.5f),
	m_fov(p_fov),
	m_ratio(static_cast<float>(p_windowWidth) / static_cast<float>(p_windowHeight)),
	m_near(p_near),
	m_far(p_far)
{
	UpdateProjectionMatrix();
	UpdateViewMatrix();
	UpdateViewProjectionMatrix();
}

std::pair<int32_t, int32_t> Rasterizer::Entities::Camera::ProjectToCameraSpace(const glm::vec3& p_point) const
{
	return std::make_pair<int32_t, int32_t>
	(
		static_cast<int32_t>(((p_point.x * 0.2f) + 1) * m_windowHalfWidth),
		static_cast<int32_t>(m_windowHeight - ((p_point.y * 0.2f) + 1) * m_windowHalfHeight)
	);
}

void Rasterizer::Entities::Camera::UpdateProjectionMatrix()
{
	m_projectionMatrix = glm::perspective(m_fov, m_ratio, m_near, m_far);
}

void Rasterizer::Entities::Camera::UpdateViewMatrix()
{
	auto debug = transform.GetWorldPosition();
	m_viewMatrix = glm::lookAt(transform.GetWorldPosition(), m_lookAt, m_upVector);
}

void Rasterizer::Entities::Camera::UpdateViewProjectionMatrix()
{
	m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
}

const glm::mat4& Rasterizer::Entities::Camera::GetProjectionMatrix() const
{
	return m_projectionMatrix;
}

const glm::mat4& Rasterizer::Entities::Camera::GetViewMatrix() const
{
	return m_viewMatrix;
}

const glm::mat4& Rasterizer::Entities::Camera::GetViewProjectionMatrix() const
{
	return m_viewProjectionMatrix;
}
