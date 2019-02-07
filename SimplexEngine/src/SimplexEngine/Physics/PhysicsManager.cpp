/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Physics/PhysicsManager.h"
#include "SimplexEngine/Scenes/SceneManager.h"

SimplexEngine::Physics::PhysicsManager::PhysicsManager()
{
	m_collisionConfig = new btDefaultCollisionConfiguration();
	m_dispatcher = new btCollisionDispatcher(m_collisionConfig);
	m_broadphase = new btDbvtBroadphase();
	m_solver = new btSequentialImpulseConstraintSolver();
	m_world = new btSimpleDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfig);
	m_world->setGravity(btVector3(0.0f, -9.8f, 0.0f));
}

SimplexEngine::Physics::PhysicsManager::~PhysicsManager()
{
}

void SimplexEngine::Physics::PhysicsManager::SetGravity(const glm::vec3 & p_gravity)
{
	m_world->setGravity(btVector3(p_gravity.x, p_gravity.y, p_gravity.z));
}

void SimplexEngine::Physics::PhysicsManager::ProvideSceneManager(Scenes::SceneManager& p_sceneManager)
{
	m_sceneManager = &p_sceneManager;

	m_sceneManager->ComponentAddedEvent.AddListener(std::bind(&PhysicsManager::OnComponentAdded, this, std::placeholders::_1));
	m_sceneManager->ComponentRemovedEvent.AddListener(std::bind(&PhysicsManager::OnComponentRemoved, this, std::placeholders::_1));
}

void SimplexEngine::Physics::PhysicsManager::Update(float p_deltaTime)
{
	if (m_sceneManager)
	{
		m_world->stepSimulation(p_deltaTime);

		for (auto& element : m_sceneManager->GetCurrentScene()->GetActors())
		{
			auto rigidbodyComponent = element->GetComponent<Components::RigidbodyComponent>();
			if (rigidbodyComponent)
				MoveRigidbody(*rigidbodyComponent);
		}
	}
}

void SimplexEngine::Physics::PhysicsManager::MoveRigidbody(Components::RigidbodyComponent & p_target)
{
	p_target.GetBody()->getMotionState()->getWorldTransform(*p_target.GetTransform());

	btVector3 newPosition = p_target.GetTransform()->getOrigin();
	btQuaternion newRotation = p_target.GetTransform()->getRotation();

	p_target.owner->transform.SetLocalPosition(glm::vec3(newPosition.getX(), newPosition.getY(), newPosition.getZ()));
	p_target.owner->transform.SetLocalRotation(glm::quat(newRotation.getW(), newRotation.getX(), newRotation.getY(), newRotation.getZ()));
}

void SimplexEngine::Physics::PhysicsManager::OnComponentAdded(Components::AActorComponent& p_component)
{
	Components::RigidbodyComponent* rigidbodyComponent = dynamic_cast<Components::RigidbodyComponent*>(&p_component);
	if (rigidbodyComponent)
	{
		m_world->addRigidBody(rigidbodyComponent->GetBody());
	}
}

void SimplexEngine::Physics::PhysicsManager::OnComponentRemoved(Components::AActorComponent & p_component)
{
	Components::RigidbodyComponent* rigidbodyComponent = dynamic_cast<Components::RigidbodyComponent*>(&p_component);
	if (rigidbodyComponent)
	{
		m_world->removeRigidBody(rigidbodyComponent->GetBody());
	}
}
