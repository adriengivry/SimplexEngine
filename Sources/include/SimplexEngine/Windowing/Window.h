#pragma once
#ifndef _WINDOW_H
#define _WINDOW_H

#include <tuple>
#include <string>

#include <glm/glm.hpp>

#include "SimplexEngine/API/Export.h"
#include "SimplexEngine/Windowing/EWindowState.h"

namespace SimplexEngine::Windowing
{
	/**
	* The window class is using SDL to create the window context
	*/
	class API_SIMPLEXENGINE Window final
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
		* Return the SDL_GLContext instance
		*/
		void* GetGLContext() const;

		/**
		* Return the window width
		*/
		uint32_t GetWidth() const;

		/**
		* Return the window width
		*/
		uint32_t GetHeight() const;

		/**
		* Return the window width signed
		*/
		int32_t GetWidthSigned() const;

		/**
		* Return the window height signed
		*/
		int32_t GetHeightSigned() const;

		/**
		* Return the half of the width of the window
		*/
		int32_t GetHalfWidth() const;

		/**
		* Return the half of the width of the window
		*/
		int32_t GetHalfHeight() const;

		/**
		* Return the aspect ratio of the window
		*/
		float GetAspectRatio() const;

		/**
		* Return the window size as a pair of uint32_t
		*/
		std::pair<uint32_t, uint32_t> GetSize() const;

		/**
		* Return the window size as a pair of int32_t
		*/
		std::pair<int32_t, int32_t> GetSizeSigned() const;

		/**
		* Verify if the given point is in window
		* @param p_point
		*/
		bool IsPointInWindow(const std::pair<int32_t, int32_t>& p_point) const;

	private:
		/* Window settings */
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_halfWidth;
		uint32_t m_halfHeight;

		std::string m_title;

		float m_aspectRatio;

		/* Window current state */
		EWindowState m_windowState;

		/* SDL relatives */
		struct SDL_Window* m_sdlWindow;
		void* m_glContext;
	};
}

#endif // _WINDOW_H