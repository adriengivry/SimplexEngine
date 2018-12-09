/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _SRASTERIZATIONLIMITER_H
#define _SRASTERIZATIONLIMITER_H

#include "SimplexEngine/Rendering/Rasterizer.h"
#include "SimplexEngine/Scripts/SRasterizationLimiter.h"
#include "SimplexEngine/Scripts/IScript.h"

namespace SimplexEngine::Scripts
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
		* @param p_speed
		*/
		SRasterizationLimiter(Rendering::Rasterizer& p_rasterBoy, float p_speed);

		/**
		* Destructor of the SRasterizationLimiter.
		* It will disable rasterization limit
		*/
		virtual ~SRasterizationLimiter();

		/**
		* Update the script
		* @param p_deltaTime
		*/
		virtual void Update(float p_deltaTime) override;

	private:
		Rendering::Rasterizer& m_rasterBoy;

		float m_speed;
		float m_rasterizationLimit;
	};
}

#endif // _SRASTERIZATIONLIMITER_H