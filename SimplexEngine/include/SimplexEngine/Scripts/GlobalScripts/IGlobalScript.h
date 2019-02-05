/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _IGLOBALSCRIPT_H
#define _IGLOBALSCRIPT_H

#include "SimplexEngine/API/Export.h"
#include "SimplexEngine/Scripts/IScript.h"

namespace SimplexEngine::Scripts::GlobalScripts
{
	class API_SIMPLEXENGINE IGlobalScript : public IScript
	{
	public:
		/**
		* Update the global script
		* @parma p_deltaTime
		*/
		virtual void Update(float p_deltaTime) = 0;

		/**
		* Destrutor of IGlobalScript. You can create your destructor in child classes
		*/
		virtual ~IGlobalScript() = default;
	};
}

#endif // _IGLOBALSCRIPT_H