#pragma once
#ifndef _CLOCK_H
#define _CLOCK_H

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

		/**
		* Return the current delta time (Time since last frame)
		*/
		float GetDeltaTime() const;

		/**
		* Return the current frame rate
		*/
		float GetFramerate() const;

	private:
		uint32_t m_currentTime = 0;
		uint32_t m_lastTime = 0;
		float m_deltaTime = 0;
	};
}

#endif // _CLOCK_H
