/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Scripts/IScript.h"

#pragma once
#ifndef _SFPSCOUNTER_H
#define _SFPSCOUNTER_H

namespace Rasterizer::Scripts
{
	/**
	* Rotate an entity over time
	*/
	class SFPSCounter final : public IScript
	{
	public:
		/**
		* Constructor of the script
		*/
		SFPSCounter();

		/**
		* Update the script
		* @param p_deltaTime
		*/
		virtual void Update(float p_deltaTime) override;

	private:
		float m_logTimer;
		float m_logFrequency;
	};
}

#endif // _SFPSCOUNTER_H