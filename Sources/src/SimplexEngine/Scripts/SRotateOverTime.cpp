/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Scripts/SRotateOverTime.h"
#include "SimplexEngine/Utils/Math.h"

SimplexEngine::Scripts::SRotateOverTime::SRotateOverTime(Actors::Actor& p_target, float p_rotationSpeed) :
	m_target(p_target),
	m_rotationSpeed(p_rotationSpeed)
{
	
}

void SimplexEngine::Scripts::SRotateOverTime::Update(float p_deltaTime)
{
	m_target.transform.RotateLocal(Utils::Math::CreateQuaternionFromEuler({ 0.0f, m_rotationSpeed * p_deltaTime, 0.0f }));
}
