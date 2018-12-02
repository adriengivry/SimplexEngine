/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Entities/AEntity.h"

Rasterizer::Entities::AEntity::AEntity(AltMath::Vector3f p_position, AltMath::Quaternion p_rotation) :
	transform(p_position, p_rotation)
{
}

void Rasterizer::Entities::AEntity::SetParent(AEntity & p_parent)
{
	m_parent = &p_parent;
	transform.SetParent(m_parent->transform);
}
