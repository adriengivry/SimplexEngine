/**
* Project SimplexEngine - Example
* @author Adrien Givry
* @version 1.0
*/

#include <SimplexEngine/SimplexEngine.h>

#pragma once
#ifndef _SANDBOXSCENE_H
#define _SANDBOXSCENE_H

namespace Example::Scenes
{
	class SandboxScene final : public SimplexEngine::Scenes::AScene
	{
	public:
		SandboxScene(SCENE_PARAMETERS) : SCENE_INITIALIZATION_LIST{}

		virtual void OnLoad() override;
		virtual void OnUnload() override;
	};
}

#endif // _SANDBOXSCENE_H