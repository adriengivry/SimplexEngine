/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Entities/AEntity.h"

Rasterizer::Entities::AEntity::AEntity(glm::vec3 p_localPosition, glm::quat p_localRotation, glm::vec3 p_localScale) :
	transform(p_localPosition, p_localRotation, p_localScale)
{
}

void Rasterizer::Entities::AEntity::SetParent(AEntity & p_parent)
{
	m_parent = &p_parent;
	transform.SetParent(m_parent->transform);
}
