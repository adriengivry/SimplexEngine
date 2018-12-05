/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _SRASTERIZATIONLIMITER_H
#define _SRASTERIZATIONLIMITER_H

#include "Rasterizer/Core/RasterBoy.h"
#include "Rasterizer/Scripts/SRasterizationLimiter.h"
#include "Rasterizer/Scripts/IScript.h"

namespace Rasterizer::Scripts
{
	/**
	* Create a pseudo-animation by limiting the number of triangles to draw in the scene
	*/
	class SRasterizationLimiter final : public IScript
	{
	public:
		/**
		* Constructor
		* @param p_rasterBoy
		*/
		SRasterizationLimiter(Core::RasterBoy& p_rasterBoy);

		/**
		* Update the script
		* @param p_deltaTime
		*/
		virtual void Update(float p_deltaTime) override;

	private:
		Core::RasterBoy& m_rasterBoy;

		float m_rasterizationLimit;
	};
}

#endif // _SRASTERIZATIONLIMITER_H