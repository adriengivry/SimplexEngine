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
	glm::vec3 ownerPos = p_owner.transform.GetWorldPosition();
	glm::quat ownerRot = p_owner.transform.GetWorldRotation();

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

void SimplexEngine::Components::RigidbodyComponent::SetVelocity(const glm::vec3 & p_velocity)
{
	m_body->setLinearVelocity(btVector3(p_velocity.x, p_velocity.y, p_velocity.z));
}

glm::vec3 SimplexEngine::Components::RigidbodyComponent::GetVelocity() const
{
	auto linearVelocity = m_body->getLinearVelocity();
	return glm::vec3(linearVelocity.getX(), linearVelocity.getY(), linearVelocity.getZ());
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
