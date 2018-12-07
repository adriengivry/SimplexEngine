/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _AACTORCOMPONENT_H
#define _AACTORCOMPONENT_H

/* Forward delecaration */
namespace Rasterizer::Actors { class Actor; }

namespace Rasterizer::Components
{
	/**
	* The base class for any component
	*/
	class AActorComponent
	{
	public:
		AActorComponent(Actors::Actor& p_owner) : owner(&p_owner) {}

		virtual void Test() = 0;

	public:
		/* The owner of this component is public */
		Actors::Actor* owner;
	};
}

#endif // _AACTORCOMPONENT_H