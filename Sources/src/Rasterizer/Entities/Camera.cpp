/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Entities/Camera.h"

Rasterizer::Entities::Camera::Camera(const AltMath::Vector3f& p_position, const AltMath::Quaternion& p_rotation, float p_fov, float p_ratio, float p_near, float p_far, const AltMath::Vector3f & p_lookAt, const AltMath::Vector3f & p_upVector) :
	AEntity(p_position, p_rotation),
	m_fov(p_fov),
	m_ratio(p_ratio),
	m_near(p_near),
	m_far(p_far),
	m_lookAt(p_lookAt),
	m_upVector(p_upVector)
{
	UpdateProjectionMatrix();
	UpdateViewMatrix();
	UpdateViewProjectionMatrix();
}

void Rasterizer::Entities::Camera::UpdateProjectionMatrix()
{
	m_projectionMatrix = AltMath::Matrix4f::CreatePerspective(m_fov, m_ratio, m_near, m_far);
}

void Rasterizer::Entities::Camera::UpdateViewMatrix()
{
	AltMath::Vector3f worldPosition = transform.GetWorldPosition();

	m_viewMatrix = AltMath::Matrix4f::CreateView(worldPosition.x, worldPosition.y, worldPosition.z, m_lookAt.x, m_lookAt.y, m_lookAt.z, m_upVector.x, m_upVector.y, m_upVector.z);
}

void Rasterizer::Entities::Camera::UpdateViewProjectionMatrix()
{
	m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
}

const AltMath::Matrix4f & Rasterizer::Entities::Camera::GetProjectionMatrix() const
{
	return m_projectionMatrix;
}

const AltMath::Matrix4f & Rasterizer::Entities::Camera::GetViewMatrix() const
{
	return m_viewMatrix;
}

const AltMath::Matrix4f & Rasterizer::Entities::Camera::GetViewProjectionMatrix() const
{
	return m_viewProjectionMatrix;
}
