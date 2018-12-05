/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include <string>
#include <algorithm>

#include "Rasterizer/Scripts/SRasterizationLimiter.h"
#include "Rasterizer/Utils/IniIndexer.h"

Rasterizer::Scripts::SRasterizationLimiter::SRasterizationLimiter(Core::RasterBoy& p_rasterBoy) : m_rasterBoy(p_rasterBoy)
{
	m_rasterizationLimit = 0.0f;

	m_rasterBoy.LimitTriangleRasterization(true);
}

void Rasterizer::Scripts::SRasterizationLimiter::Update(float p_deltaTime)
{
	m_rasterizationLimit += p_deltaTime * Utils::IniIndexer::Application->Get<float>("rasterization_limiter_speed");

	/* Prevent the overflow of float */
	m_rasterizationLimit = std::min(m_rasterizationLimit, 10000000.0f);

	m_rasterBoy.SetRasterizedTriangleLimit(static_cast<uint64_t>(m_rasterizationLimit));
}
