/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _ISCENESCRIPT_H
#define _ISCENESCRIPT_H

#include "SimplexEngine/Scripts/IScript.h"

namespace SimplexEngine::Scripts::SceneScripts
{
	class ISceneScript : public IScript
	{
	public:
		/**
		* Update the scene script
		* @parma p_deltaTime
		*/
		virtual void Update(float p_deltaTime) = 0;

		/**
		* Destrutor of ISceneScript. You can create your destructor in child classes
		*/
		virtual ~ISceneScript() = default;
	};
}

#endif // _ISCENESCRIPT_H