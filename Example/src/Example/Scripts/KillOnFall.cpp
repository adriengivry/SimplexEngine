/**
* Project SimplexEngine - Example
* @author Adrien Givry
* @version 1.0
*/

#include "Example/Scripts/KillOnFall.h"

Example::Scripts::KillOnFall::KillOnFall(SimplexEngine::Actors::Actor& p_owner, float p_killHeight) :
	m_killHeight(p_killHeight), ABehaviour(p_owner)
{
}

void Example::Scripts::KillOnFall::Update(float p_deltaTime)
{
	if (owner.transform.GetLocalPosition().y <= m_killHeight)
		owner.Destroy();
}
