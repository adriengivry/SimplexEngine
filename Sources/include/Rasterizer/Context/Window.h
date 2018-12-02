#pragma once
#ifndef _WINDOW_H
#define _WINDOW_H

#include <tuple>
#include <string>

#include <glm/glm.hpp>

#include "Rasterizer/Context/EWindowState.h"

namespace Rasterizer::Context
{
	/**
	* The window class is using SDL to create the window context
	*/
	class Window final
	{
	public:
		/**
		* Create the window
		* @param p_title
		* @param p_width
		* @param p_heigt
		*/
		Window(const std::string& p_title, uint16_t p_width, uint16_t p_height);

		/**
		* Destructor of the window, responsible of the SDL_Window memory free
		*/
		~Window();

		/**
		* Check if the window is opened
		*/
		bool IsOpened() const;

		/**
		* Return the current state of the window
		*/
		EWindowState GetWindowState() const;

		/**
		* Return the SDL_Window* instance
		*/
		struct SDL_Window* GetSDLWindow() const;

		/**
		* Return the window width
		*/
		uint32_t GetWidth() const;

		/**
		* Return the window width
		*/
		uint32_t GetHeight() const;

		/**
		* Return the aspect ratio of the window
		*/
		float GetAspectRatio() const;

		/**
		* Return the window size as a pair of uint16_t
		*/
		std::pair<uint16_t, uint16_t> GetSize() const;

		/**
		* Verify if the given point is in window
		* @param p_point
		*/
		bool IsPointInWindow(const std::pair<uint32_t, uint32_t>& p_point) const;

	private:
		/* Window settings */
		uint16_t m_width;
		uint16_t m_height;
		std::string m_title;

		float m_aspectRatio;

		/* Window current state */
		EWindowState m_windowState;

		/* SDL relatives */
		struct SDL_Window* m_sdlWindow;
	};
}

#endif // _WINDOW_H