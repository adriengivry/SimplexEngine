/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Components/AColliderComponent.h"

SimplexEngine::Components::AColliderComponent::AColliderComponent(SimplexEngine::Actors::Actor& p_owner) :
	AActorComponent(p_owner)
{
}

SimplexEngine::Components::AColliderComponent::~AColliderComponent()
{
}

btCollisionShape * SimplexEngine::Components::AColliderComponent::GetShape()
{
	return m_shape;
}
