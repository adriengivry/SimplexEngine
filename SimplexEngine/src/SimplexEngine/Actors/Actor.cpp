#include "SimplexEngine/Actors/Actor.h"

void SimplexEngine::Actors::Actor::Destroy()
{
	m_destroyed = true;
}

bool SimplexEngine::Actors::Actor::IsDestroyed() const
{
	return m_destroyed;
}
