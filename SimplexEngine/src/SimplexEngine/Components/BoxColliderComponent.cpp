/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Components/BoxColliderComponent.h"

SimplexEngine::Components::BoxColliderComponent::BoxColliderComponent(SimplexEngine::Actors::Actor& p_owner, const glm::vec3 & p_size) :
	AColliderComponent(p_owner)
{
	m_shape = new btBoxShape(btVector3(p_size.x, p_size.y, p_size.z));
}

SimplexEngine::Components::BoxColliderComponent::~BoxColliderComponent()
{
}
