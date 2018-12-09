/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include <string>
#include <algorithm>

#include "SimplexEngine/Scripts/SRasterizationLimiter.h"
#include "SimplexEngine/Utils/IniIndexer.h"

SimplexEngine::Scripts::SRasterizationLimiter::SRasterizationLimiter(Rendering::Rasterizer& p_rasterBoy, float p_speed) : m_rasterBoy(p_rasterBoy), m_speed(p_speed)
{
	m_rasterizationLimit = 0.0f;

	m_rasterBoy.LimitTriangleRasterization(true);
}

SimplexEngine::Scripts::SRasterizationLimiter::~SRasterizationLimiter()
{
	m_rasterBoy.LimitTriangleRasterization(false);
}

void SimplexEngine::Scripts::SRasterizationLimiter::Update(float p_deltaTime)
{
	float previousLimit = m_rasterizationLimit;
	m_rasterizationLimit += p_deltaTime * m_speed;

	/* Prevent the overflow of float */
	if (m_rasterizationLimit < previousLimit)
		m_rasterizationLimit = previousLimit;

	m_rasterBoy.SetRasterizedTriangleLimit(static_cast<uint64_t>(m_rasterizationLimit));
}
