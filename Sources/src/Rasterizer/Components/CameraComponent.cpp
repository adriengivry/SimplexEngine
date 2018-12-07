/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include <glm/gtc/matrix_transform.hpp>

#include "Rasterizer/Components/CameraComponent.h"
#include "Rasterizer/Actors/Actor.h"

Rasterizer::Components::CameraComponent::CameraComponent(Actors::Actor& p_owner, const glm::vec3 & p_upVector, float p_ratio, float p_fov, float p_near, float p_far) :
	AActorComponent(p_owner),
	m_upVector(p_upVector),
	m_ratio(p_ratio),
	m_fov(p_fov),
	m_near(p_near),
	m_far(p_far)
{
	UpdateForwardVector();
	UpdateViewProjectionMatrix();

	owner->transform.TransformChangedEvent.AddListener(std::bind(&CameraComponent::UpdateForwardVector, this));
	owner->transform.TransformChangedEvent.AddListener(std::bind(&CameraComponent::UpdateViewProjectionMatrix, this));
}

const glm::vec3 & Rasterizer::Components::CameraComponent::GetForward() const
{
	return m_forward;
}

void Rasterizer::Components::CameraComponent::UpdateForwardVector()
{
	m_forward = glm::normalize(owner->transform.GetWorldRotation() * glm::vec3(0.0f, 0.0f, -1.0f));
}

void Rasterizer::Components::CameraComponent::UpdateProjectionMatrix()
{
	m_projectionMatrix = glm::perspective(glm::radians(m_fov), m_ratio, m_near, m_far);
}

void Rasterizer::Components::CameraComponent::UpdateViewMatrix()
{
	m_viewMatrix = glm::lookAt(owner->transform.GetWorldPosition(), owner->transform.GetWorldPosition() + m_forward, m_upVector);
}

void Rasterizer::Components::CameraComponent::UpdateViewProjectionMatrix()
{
	UpdateViewMatrix();
	UpdateProjectionMatrix();

	m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
}

const glm::mat4& Rasterizer::Components::CameraComponent::GetProjectionMatrix() const
{
	return m_projectionMatrix;
}

const glm::mat4& Rasterizer::Components::CameraComponent::GetViewMatrix() const
{
	return m_viewMatrix;
}

const glm::mat4& Rasterizer::Components::CameraComponent::GetViewProjectionMatrix() const
{
	return m_viewProjectionMatrix;
}
