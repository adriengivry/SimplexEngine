/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include <functional>

#include <glm/gtc/matrix_transform.hpp>

#include "Rasterizer/Entities/Camera.h"

Rasterizer::Entities::Camera::Camera(const glm::vec3 & p_position, const glm::vec3 & p_lookAt, const glm::vec3 & p_upVector, float p_ratio, float p_fov, float p_near, float p_far) :
	AEntity(p_position),
	m_lookAt(p_lookAt),
	m_upVector(p_upVector),
	m_ratio(p_ratio),
	m_fov(p_fov),
	m_near(p_near),
	m_far(p_far)
{
	UpdateViewProjectionMatrix();

	/* Automate the view projection update with an even listener */
	transform.TransformChangedEvent.AddListener(std::bind(&Camera::UpdateViewProjectionMatrix, this));
}

void Rasterizer::Entities::Camera::UpdateProjectionMatrix()
{
	m_projectionMatrix = glm::perspective(glm::radians(m_fov), m_ratio, m_near, m_far);
}

void Rasterizer::Entities::Camera::UpdateViewMatrix()
{
	m_viewMatrix = glm::lookAt(transform.GetWorldPosition(), m_lookAt, m_upVector);
}

void Rasterizer::Entities::Camera::UpdateViewProjectionMatrix()
{
	UpdateViewMatrix();
	UpdateProjectionMatrix();

	m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
}

void Rasterizer::Entities::Camera::Move(const glm::vec3 p_translation)
{
	m_lookAt += p_translation;
	transform.SetPosition(transform.GetLocalPosition() + p_translation);
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
