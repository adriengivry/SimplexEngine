/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Components/CapsuleColliderComponent.h"

SimplexEngine::Components::CapsuleColliderComponent::CapsuleColliderComponent(SimplexEngine::Actors::Actor& p_owner, float p_radius, float p_height) :
	AColliderComponent(p_owner)
{
	m_shape = new btCapsuleShape(p_radius, p_height);
}

SimplexEngine::Components::CapsuleColliderComponent::~CapsuleColliderComponent()
{
}
