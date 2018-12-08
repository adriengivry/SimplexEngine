/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include <string>
#include <algorithm>

#include "Rasterizer/Scripts/SRasterizationLimiter.h"
#include "Rasterizer/Utils/IniIndexer.h"

Rasterizer::Scripts::SRasterizationLimiter::SRasterizationLimiter(Rendering::RasterBoy& p_rasterBoy, float p_speed) : m_rasterBoy(p_rasterBoy), m_speed(p_speed)
{
	m_rasterizationLimit = 0.0f;

	m_rasterBoy.LimitTriangleRasterization(true);
}

Rasterizer::Scripts::SRasterizationLimiter::~SRasterizationLimiter()
{
	m_rasterBoy.LimitTriangleRasterization(false);
}

void Rasterizer::Scripts::SRasterizationLimiter::Update(float p_deltaTime)
{
	float previousLimit = m_rasterizationLimit;
	m_rasterizationLimit += p_deltaTime * m_speed;

	/* Prevent the overflow of float */
	if (m_rasterizationLimit < previousLimit)
		m_rasterizationLimit = previousLimit;

	m_rasterBoy.SetRasterizedTriangleLimit(static_cast<uint64_t>(m_rasterizationLimit));
}
