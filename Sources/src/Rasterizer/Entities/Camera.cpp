/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include <functional>

#include <glm/gtc/matrix_transform.hpp>

#include "Rasterizer/Entities/Camera.h"

Rasterizer::Entities::Camera::Camera(const glm::vec3 & p_position, const glm::quat& p_rotation, const glm::vec3 & p_upVector, float p_ratio, float p_fov, float p_near, float p_far) :
	AEntity(p_position, p_rotation),
	m_upVector(p_upVector),
	m_ratio(p_ratio),
	m_fov(p_fov),
	m_near(p_near),
	m_far(p_far)
{
	UpdateForwardVector();
	UpdateViewProjectionMatrix();

	transform.TransformChangedEvent.AddListener(std::bind(&Camera::UpdateForwardVector, this));
	transform.TransformChangedEvent.AddListener(std::bind(&Camera::UpdateViewProjectionMatrix, this));
}

const glm::vec3 & Rasterizer::Entities::Camera::GetForward() const
{
	return m_forward;
}

void Rasterizer::Entities::Camera::UpdateForwardVector()
{
	m_forward = glm::normalize(transform.GetWorldRotation() * glm::vec3(0.0f, 0.0f, -1.0f));
}

void Rasterizer::Entities::Camera::UpdateProjectionMatrix()
{
	m_projectionMatrix = glm::perspective(glm::radians(m_fov), m_ratio, m_near, m_far);
}

void Rasterizer::Entities::Camera::UpdateViewMatrix()
{
	m_viewMatrix = glm::lookAt(transform.GetWorldPosition(), transform.GetWorldPosition() + m_forward, m_upVector);
}

void Rasterizer::Entities::Camera::UpdateViewProjectionMatrix()
{
	UpdateViewMatrix();
	UpdateProjectionMatrix();

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
