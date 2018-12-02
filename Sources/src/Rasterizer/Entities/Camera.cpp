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

AltMath::Vector2i Rasterizer::Entities::Camera::ProjectToCameraSpace(const AltMath::Vector3f& p_point)
{
	const float width = 1280;
	const float height = 720;

	const float widthHalf = width * 0.5f;
	const float heightHalf = height * 0.5f;

	return AltMath::Vector2i(static_cast<int>(((p_point.x / 5.0f) + 1) * widthHalf), static_cast<int>(height - ((p_point.y / 5.0f) + 1) * heightHalf));
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
