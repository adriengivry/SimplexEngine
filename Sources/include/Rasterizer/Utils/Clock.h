#pragma once
#ifndef _CLOCK_H
#define _CLOCK_H

#include <SDL.h>

namespace Rasterizer::Utils
{
	/**
	* The Clock class is responsible for the delta time calculation
	*/
	class Clock final
	{
	public:
		/**
		* Updates the delta time
		*/
		void Tick();

		float GetDeltaTime() const;

	private:
		uint32_t m_currentTime = 0;
		uint32_t m_lastTime = 0;
		float m_deltaTime = 0;
	};
}

#endif // _CLOCK_H
