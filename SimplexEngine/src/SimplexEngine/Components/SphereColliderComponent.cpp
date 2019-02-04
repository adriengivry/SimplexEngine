/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Components/SphereColliderComponent.h"

SimplexEngine::Components::SphereColliderComponent::SphereColliderComponent(SimplexEngine::Actors::Actor& p_owner, float p_radius) :
	AColliderComponent(p_owner)
{
	m_shape = new btSphereShape(p_radius);
}

SimplexEngine::Components::SphereColliderComponent::~SphereColliderComponent()
{
}
