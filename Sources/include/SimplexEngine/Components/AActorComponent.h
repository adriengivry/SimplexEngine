/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _AACTORCOMPONENT_H
#define _AACTORCOMPONENT_H

#include "SimplexEngine/API/Export.h"

/* Forward delecaration */
namespace SimplexEngine::Actors { class Actor; }

namespace SimplexEngine::Components
{
	/**
	* The base class for any component
	*/
	class API_SIMPLEXENGINE AActorComponent
	{
	public:
		AActorComponent(Actors::Actor& p_owner) : owner(&p_owner) {}

		virtual ~AActorComponent() {}

	public:
		/* The owner of this component is public */
		Actors::Actor* owner;
	};
}

#endif // _AACTORCOMPONENT_H