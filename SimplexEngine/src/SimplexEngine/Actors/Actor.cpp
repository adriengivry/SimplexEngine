#include "SimplexEngine/Actors/Actor.h"

void SimplexEngine::Actors::Actor::UpdateBehaviours(float p_deltaTime)
{
	for (auto& behaviour : m_behaviours)
		behaviour->Update(p_deltaTime);
}

void SimplexEngine::Actors::Actor::Destroy()
{
	m_destroyed = true;
}

bool SimplexEngine::Actors::Actor::IsDestroyed() const
{
	return m_destroyed;
}
