/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _IBEHAVIOUR_H
#define _IBEHAVIOUR_H

#include "SimplexEngine/API/Export.h"
#include "SimplexEngine/Scripts/IScript.h"

namespace SimplexEngine::Actors { class Actor; }

namespace SimplexEngine::Scripts::Behaviours
{
	class API_SIMPLEXENGINE ABehaviour : public IScript
	{
	public:
		/**
		* Create a behaviour
		* @param p_owner
		*/
		ABehaviour(Actors::Actor& p_owner);

		/**
		* Update the behaviour
		* @parma p_deltaTime
		*/
		virtual void Update(float p_deltaTime) = 0;

		/**
		* Destrutor of IBehaviour. You can create your destructor in child classes
		*/
		virtual ~ABehaviour() = default;

	public:
		Actors::Actor& owner;
	};
}

#endif // _IBEHAVIOUR_H