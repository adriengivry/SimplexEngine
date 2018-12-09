/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _ISCRIPT_H
#define _ISCRIPT_H

#include "SimplexEngine/API/Export.h"

namespace SimplexEngine::Scripts
{
	class API_SIMPLEXENGINE IScript
	{
	public:
		/**
		* Update the script
		* @parma p_deltaTime
		*/
		virtual void Update(float p_deltaTime) = 0;

		/**
		* Destrutor of IScript. You can create your destructor in child classes
		*/
		virtual ~IScript() = default;
	};
}

#endif // _ISCRIPT_H