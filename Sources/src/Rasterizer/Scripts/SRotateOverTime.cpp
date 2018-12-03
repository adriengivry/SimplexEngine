/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Scripts/SRotateOverTime.h"
#include "Rasterizer/Utils/Math.h"

Rasterizer::Scripts::SRotateOverTime::SRotateOverTime(Entities::AEntity & p_target, float p_rotationSpeed) :
	m_target(p_target),
	m_rotationSpeed(p_rotationSpeed),
	m_rotationAngle(0.0f)
{
}

void Rasterizer::Scripts::SRotateOverTime::Update(float p_deltaTime)
{
	m_target.transform.SetRotation(Utils::Math::CreateQuaternionFromEuler({ 0.0f, m_rotationAngle, 0.0f }));
	m_rotationAngle += m_rotationSpeed * p_deltaTime;
}
