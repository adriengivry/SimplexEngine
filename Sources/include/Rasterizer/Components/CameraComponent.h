/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _CAMERACOMPONENT_H
#define _CAMERACOMPONENT_H

#include "Rasterizer/Components/AActorComponent.h"

namespace Rasterizer::Components
{
	/**
	* The camera component is a component that allow an actor to get
	* interpreted as a scene camera
	*/
	class CameraComponent : public AActorComponent
	{

	};
}

#endif // _CAMERACOMPONENT_H