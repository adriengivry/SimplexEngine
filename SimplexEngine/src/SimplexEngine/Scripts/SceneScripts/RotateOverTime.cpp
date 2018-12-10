/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Scripts/SceneScripts/RotateOverTime.h"
#include "SimplexEngine/Maths/QuaternionFactory.h"

SimplexEngine::Scripts::SceneScripts::RotateOverTime::RotateOverTime(Actors::Actor& p_target, float p_rotationSpeed, const glm::vec3& p_rotationAxis) :
	m_target(p_target),
	m_rotationSpeed(p_rotationSpeed),
	m_rotationAxis(p_rotationAxis)
{
	
}

void SimplexEngine::Scripts::SceneScripts::RotateOverTime::Update(float p_deltaTime)
{
	m_target.transform.RotateLocal(Maths::QuaternionFactory::CreateFromEuler(m_rotationAxis * m_rotationSpeed * p_deltaTime));
}
