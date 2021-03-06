/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#include "SimplexEngine/Data/Transform.h"

SimplexEngine::Data::Transform::Transform(glm::vec3 p_localPosition, glm::quat p_localRotation, glm::vec3 p_localScale) :
	m_parent(nullptr)
{
	GenerateMatrices(p_localPosition, p_localRotation, p_localScale);
}

void SimplexEngine::Data::Transform::SetParent(Data::Transform& p_parent)
{
	m_parent = &p_parent;

	m_parent->TransformChangedEvent.AddListener(std::bind(&Transform::UpdateWorldMatrices, this));

	UpdateWorldMatrices();
}

bool SimplexEngine::Data::Transform::HasParent() const
{
	return m_parent != nullptr;
}

void SimplexEngine::Data::Transform::GenerateMatrices(glm::vec3 p_position, glm::quat p_rotation, glm::vec3 p_scale)
{
	m_localMatrix = glm::translate(glm::mat4(1.0f), p_position) * glm::toMat4(p_rotation) * glm::scale(glm::mat4(1.0f), p_scale);
	PreDecomposeLocalMatrix();

	UpdateWorldMatrices();
}

void SimplexEngine::Data::Transform::UpdateWorldMatrices()
{
	m_worldMatrix = HasParent() ? m_parent->m_worldMatrix * m_localMatrix : m_localMatrix;
	PreDecomposeWorldMatrix();

	TransformChangedEvent.Invoke();
}

void SimplexEngine::Data::Transform::SetLocalPosition(glm::vec3 p_newPosition)
{
	GenerateMatrices(p_newPosition, m_localRotation, m_localScale);
}

void SimplexEngine::Data::Transform::SetLocalRotation(glm::quat p_newRotation)
{
	GenerateMatrices(m_localPosition, p_newRotation, m_localScale);
}

void SimplexEngine::Data::Transform::SetLocalScale(glm::vec3 p_newScale)
{
	GenerateMatrices(m_localPosition, m_localRotation, p_newScale);
}

void SimplexEngine::Data::Transform::TranslateLocal(const glm::vec3& p_translation)
{
	SetLocalPosition(m_localPosition + p_translation);
}

void SimplexEngine::Data::Transform::RotateLocal(const glm::quat& p_rotation)
{
	SetLocalRotation(m_localRotation * p_rotation);
}

void SimplexEngine::Data::Transform::ScaleLocal(const glm::vec3 & p_scale)
{
	SetLocalScale(m_localScale * p_scale);
}

const glm::vec3 & SimplexEngine::Data::Transform::GetLocalPosition() const
{
	return m_localPosition;
}

const glm::quat & SimplexEngine::Data::Transform::GetLocalRotation() const
{
	return m_localRotation;
}

const glm::vec3 & SimplexEngine::Data::Transform::GetLocalScale() const
{
	return m_localScale;
}

const glm::vec3 & SimplexEngine::Data::Transform::GetWorldPosition() const
{
	return m_worldPosition;
}

const glm::quat & SimplexEngine::Data::Transform::GetWorldRotation() const
{
	return m_worldRotation;
}

const glm::vec3 & SimplexEngine::Data::Transform::GetWorldScale() const
{
	return m_worldScale;
}

const glm::mat4 & SimplexEngine::Data::Transform::GetLocalMatrix() const
{
	return m_localMatrix;
}

const glm::mat4 & SimplexEngine::Data::Transform::GetWorldMatrix() const
{
	return m_worldMatrix;
}

void SimplexEngine::Data::Transform::PreDecomposeWorldMatrix()
{
	/* Not used */
	glm::vec3 skew;
	glm::vec4 perspective;

	glm::decompose(m_worldMatrix, m_worldScale, m_worldRotation, m_worldPosition, skew, perspective);

	m_worldRotation = glm::conjugate(m_worldRotation);

}

void SimplexEngine::Data::Transform::PreDecomposeLocalMatrix()
{
	/* Not used */
	glm::vec3 skew;
	glm::vec4 perspective;

	glm::decompose(m_localMatrix, m_localScale, m_localRotation, m_localPosition, skew, perspective);

	m_localRotation = glm::conjugate(m_localRotation);
}

void SimplexEngine::Data::Transform::PreDecomposeMatrices()
{
	PreDecomposeLocalMatrix();
	PreDecomposeWorldMatrix();
}
