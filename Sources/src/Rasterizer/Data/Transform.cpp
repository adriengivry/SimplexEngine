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

void Rasterizer::Data::Transform::SetParent(Data::Transform& p_parent, bool p_addChild)
{
	m_parent = &p_parent;

	UpdateWorldMatrices();

	p_parent.TransformChangedEvent.AddListener(std::bind(&Transform::UpdateWorldMatrices, this));
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

bool Rasterizer::Data::Transform::HasParent() const
{
	return m_parent != nullptr;
}

void Rasterizer::Data::Transform::SetPosition(glm::vec3 p_newPosition)
{
	GenerateMatrices(p_newPosition, GetLocalRotation());
}

void Rasterizer::Data::Transform::SetRotation(glm::quat p_newRotation)
{
	GenerateMatrices(GetLocalPosition(), p_newRotation);
}

void Rasterizer::Data::Transform::Translate(const glm::vec3& p_translation)
{
	SetPosition(GetLocalPosition() + p_translation);
}

void Rasterizer::Data::Transform::Rotate(const glm::quat& p_rotation)
{
	SetRotation(GetLocalRotation() * p_rotation);
}

glm::vec3 Rasterizer::Data::Transform::GetLocalPosition()
{
	return glm::vec3(m_localMatrix[3][0], m_localMatrix[3][1], m_localMatrix[3][2]);
}

glm::quat Rasterizer::Data::Transform::GetLocalRotation()
{
	glm::mat3 rotationMatrix(m_localMatrix[0][0], m_localMatrix[0][1], m_localMatrix[0][2], m_localMatrix[1][0], m_localMatrix[1][1], m_localMatrix[1][2], m_localMatrix[2][0], m_localMatrix[2][1], m_localMatrix[2][2]);
	return glm::quat(rotationMatrix);
}

glm::vec3 Rasterizer::Data::Transform::GetWorldPosition()
{
	return glm::vec3(m_worldMatrix[3][0], m_worldMatrix[3][1], m_worldMatrix[3][2]);
}

glm::quat Rasterizer::Data::Transform::GetWorldRotation()
{
	glm::mat3 rotationMatrix(m_worldMatrix[0][0], m_worldMatrix[0][1], m_worldMatrix[0][2], m_worldMatrix[1][0], m_worldMatrix[1][1], m_worldMatrix[1][2], m_worldMatrix[2][0], m_worldMatrix[2][1], m_worldMatrix[2][2]);
	return glm::quat(rotationMatrix);
}

const glm::mat4 & Rasterizer::Data::Transform::GetLocalMatrix() const
{
	return m_localMatrix;
}

const glm::mat4 & Rasterizer::Data::Transform::GetWorldMatrix() const
{
	return m_worldMatrix;
}
