/**
* Project SimplexEngine - Example
* @author Adrien Givry
* @version 1.0
*/

#include <SimplexEngine/SimplexEngine.h>

#pragma once
#ifndef _DEMOSCENE_H
#define _DEMOSCENE_H

namespace Example::Scenes
{
	class DemoScene final : public SimplexEngine::Scenes::AScene
	{
	public:
		DemoScene(SCENE_PARAMETERS) : SCENE_INITIALIZATION_LIST{}

		virtual void OnLoad() override;
		virtual void OnUnload() override;
	};
}

#endif // _DEMOSCENE_H