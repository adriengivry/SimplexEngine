/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#include "Rasterizer/Data/Transform.h"

Rasterizer::Data::Transform::Transform(glm::vec3 p_localPosition, glm::quat p_localRotation) :
	m_parent(nullptr)
{
	GenerateMatrices(p_localPosition, p_localRotation);
}

void Rasterizer::Data::Transform::SetParent(Data::Transform& p_parent)
{
	m_parent = &p_parent;

	UpdateWorldMatrices();
}

bool Rasterizer::Data::Transform::HasParent() const
{
	return m_parent != nullptr;
}

void Rasterizer::Data::Transform::GenerateMatrices(glm::vec3 p_position, glm::quat p_rotation)
{
	m_localMatrix = glm::translate(glm::mat4(1.0f), p_position) * glm::toMat4(p_rotation);

	UpdateWorldMatrices();
}

void Rasterizer::Data::Transform::UpdateWorldMatrices()
{;
	m_worldMatrix = HasParent() ? m_parent->GetWorldMatrix() * m_localMatrix : m_localMatrix;

	TransformChangedEvent.Invoke();
}

void Rasterizer::Data::Transform::SetLocalPosition(glm::vec3 p_newPosition)
{
	GenerateMatrices(p_newPosition, GetLocalRotation());
}

void Rasterizer::Data::Transform::SetLocalRotation(glm::quat p_newRotation)
{
	GenerateMatrices(GetLocalPosition(), p_newRotation);
}

void Rasterizer::Data::Transform::TranslateLocal(const glm::vec3& p_translation)
{
	SetLocalPosition(GetLocalPosition() + p_translation);
}

void Rasterizer::Data::Transform::RotateLocal(const glm::quat& p_rotation)
{
	SetLocalRotation(GetLocalRotation() * p_rotation);
}

glm::vec3 Rasterizer::Data::Transform::GetLocalPosition() const
{
	return glm::vec3(m_localMatrix[3]);
}

glm::quat Rasterizer::Data::Transform::GetLocalRotation() const
{
	return glm::quat(glm::mat3(m_localMatrix[0], m_localMatrix[1], m_localMatrix[2]));
}

glm::vec3 Rasterizer::Data::Transform::GetWorldPosition() const
{
	return glm::vec3(m_worldMatrix[3]);
}

glm::quat Rasterizer::Data::Transform::GetWorldRotation() const
{
	return glm::quat(glm::mat3(m_worldMatrix[0], m_worldMatrix[1], m_worldMatrix[2]));
}

const glm::mat4 & Rasterizer::Data::Transform::GetLocalMatrix() const
{
	return m_localMatrix;
}

const glm::mat4 & Rasterizer::Data::Transform::GetWorldMatrix() const
{
	return m_worldMatrix;
}
