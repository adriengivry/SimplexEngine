/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Scripts/SRotateOverTime.h"
#include "Rasterizer/Utils/Math.h"

Rasterizer::Scripts::SRotateOverTime::SRotateOverTime(Actors::Actor& p_target, float p_rotationSpeed) :
	m_target(p_target),
	m_rotationSpeed(p_rotationSpeed)
{
	
}

void Rasterizer::Scripts::SRotateOverTime::Update(float p_deltaTime)
{
	m_target.transform.RotateLocal(Utils::Math::CreateQuaternionFromEuler({ 0.0f, m_rotationSpeed * p_deltaTime, 0.0f }));
}
