/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Scripts/SceneScripts/RotateOverTime.h"
#include "SimplexEngine/Maths/QuaternionFactory.h"

SimplexEngine::Scripts::SceneScripts::RotateOverTime::RotateOverTime(Actors::Actor& p_target, float p_rotationSpeed) :
	m_target(p_target),
	m_rotationSpeed(p_rotationSpeed)
{
	
}

void SimplexEngine::Scripts::SceneScripts::RotateOverTime::Update(float p_deltaTime)
{
	m_target.transform.RotateLocal(Maths::QuaternionFactory::CreateFromEuler({ 0.0f, m_rotationSpeed * p_deltaTime, 0.0f }));
}
