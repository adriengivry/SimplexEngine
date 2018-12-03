/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _CLOCK_H
#define _CLOCK_H

#include <chrono>

namespace Rasterizer::Utils
{
	/**
	* The Clock class is responsible for the delta time calculation
	*/
	class Clock final
	{
	public: 
		/**
		* Constructor
		*/
		Clock();

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

		/**
		* Return the elapsed time
		*/
		float GetElapsedTime() const;

	private:
		std::chrono::steady_clock::time_point m_currentTime;
		std::chrono::steady_clock::time_point m_lastTime;
		float m_elapsedTime = 0.0f;
		float m_deltaTime = 0.0f;
	};
}

#endif // _CLOCK_H
