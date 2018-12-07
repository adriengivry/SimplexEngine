/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _AACTORCOMPONENT_H
#define _AACTORCOMPONENT_H

#include "Rasterizer/Actors/Actor.h"

namespace Rasterizer::Components
{
	/**
	* The base class for any component
	*/
	class AActorComponent
	{
	public:
		AActorComponent(const Actors::Actor& p_owner) : owner(p_owner) {}

	public:
		/* The owner of this component is public */
		const Actors::Actor& owner;
	};
}

#endif // _AACTORCOMPONENT_H