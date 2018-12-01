/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Data/Transform.h"

Rasterizer::Data::Transform::Transform(AltMath::Vector3f p_localPosition, AltMath::Quaternion p_localRotation) :
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

void Rasterizer::Data::Transform::GenerateMatrices(AltMath::Vector3f p_position, AltMath::Quaternion p_rotation)
{
	m_localMatrix = AltMath::Matrix4f::Identity;
	m_worldMatrix = AltMath::Matrix4f::Identity;

	m_localMatrix.Translate(p_position);
	m_localMatrix *= p_rotation.ToMatrix4();

	m_worldMatrix = HasParent() ? m_parent->GetWorldMatrix() * m_localMatrix : m_localMatrix;

	TransformChangedEvent.Invoke();
}

void Rasterizer::Data::Transform::UpdateWorldMatrices()
{
	m_worldMatrix = AltMath::Matrix4f::Identity;
	m_worldMatrix = HasParent() ? m_parent->GetWorldMatrix() * m_localMatrix : m_localMatrix;

	TransformChangedEvent.Invoke();
}

bool Rasterizer::Data::Transform::HasParent() const
{
	return m_parent != nullptr;
}

void Rasterizer::Data::Transform::SetPosition(AltMath::Vector3f p_newPosition)
{
	GenerateMatrices(p_newPosition, GetLocalRotation());
}

void Rasterizer::Data::Transform::SetRotation(AltMath::Quaternion p_newRotation)
{
	GenerateMatrices(GetLocalPosition(), p_newRotation);
}

AltMath::Vector3f Rasterizer::Data::Transform::GetLocalPosition()
{
	return AltMath::Vector3f(m_localMatrix(0, 3), m_localMatrix(1, 3), m_localMatrix(2, 3));
}

AltMath::Quaternion Rasterizer::Data::Transform::GetLocalRotation()
{
	AltMath::Matrix3f rotationMatrix(m_localMatrix(0, 0), m_localMatrix(0, 1), m_localMatrix(0, 2), m_localMatrix(1, 0), m_localMatrix(1, 1), m_localMatrix(1, 2), m_localMatrix(2, 0), m_localMatrix(2, 1), m_localMatrix(2, 2));
	return AltMath::Quaternion(rotationMatrix);
}

AltMath::Vector3f Rasterizer::Data::Transform::GetWorldPosition()
{
	return AltMath::Vector3f(m_worldMatrix(0, 3), m_worldMatrix(1, 3), m_worldMatrix(2, 3));
}

AltMath::Quaternion Rasterizer::Data::Transform::GetWorldRotation()
{
	AltMath::Matrix3f rotationMatrix(m_worldMatrix(0, 0), m_worldMatrix(0, 1), m_worldMatrix(0, 2), m_worldMatrix(1, 0), m_worldMatrix(1, 1), m_worldMatrix(1, 2), m_worldMatrix(2, 0), m_worldMatrix(2, 1), m_worldMatrix(2, 2));
	return AltMath::Quaternion(rotationMatrix);
}

const AltMath::Matrix4f & Rasterizer::Data::Transform::GetLocalMatrix() const
{
	return m_localMatrix;
}

const AltMath::Matrix4f & Rasterizer::Data::Transform::GetWorldMatrix() const
{
	return m_worldMatrix;
}
