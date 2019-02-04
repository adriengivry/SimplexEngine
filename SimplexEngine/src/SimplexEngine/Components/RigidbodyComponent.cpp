/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Components/RigidbodyComponent.h"
#include "SimplexEngine/SimplexEngine.h"

SimplexEngine::Components::RigidbodyComponent::RigidbodyComponent(SimplexEngine::Actors::Actor & p_owner, float p_mass) :
	AActorComponent(p_owner)
{
	glm::vec3 ownerPos = p_owner.transform.GetLocalPosition();
	glm::quat ownerRot = p_owner.transform.GetLocalRotation();

	m_transform.setIdentity();
	m_transform.setOrigin(btVector3(ownerPos.x, ownerPos.y, ownerPos.z));
	m_transform.setRotation(btQuaternion(ownerRot.x, ownerRot.y, ownerRot.z, ownerRot.w));

	auto shape = p_owner.GetComponent<Components::AColliderComponent>()->GetShape();

	if (shape)
	{
		btVector3 inertia(0, 0, 0);
		if (p_mass != 0.0)
			shape->calculateLocalInertia(p_mass, inertia);

		m_motion = new btDefaultMotionState(m_transform);
		btRigidBody::btRigidBodyConstructionInfo info(p_mass, m_motion, shape, inertia);
		m_body = new btRigidBody(info);
		m_body->setCcdMotionThreshold(static_cast<float>(1e-7));
		m_body->setCcdSweptSphereRadius(0.5f);
	}
}

SimplexEngine::Components::RigidbodyComponent::~RigidbodyComponent()
{
}

btTransform* SimplexEngine::Components::RigidbodyComponent::GetTransform()
{
	return &m_transform;
}

btMotionState* SimplexEngine::Components::RigidbodyComponent::GetMotion()
{
	return m_motion;
}

btRigidBody* SimplexEngine::Components::RigidbodyComponent::GetBody()
{
	return m_body;
}
