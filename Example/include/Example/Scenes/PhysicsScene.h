/**
* Project SimplexEngine - Example
* @author Adrien Givry
* @version 1.0
*/

#include <SimplexEngine/SimplexEngine.h>

#pragma once
#ifndef _PHYSICSSCENE_H
#define _PHYSICSSCENE_H

namespace Example::Scenes
{
	class PhysicsScene final : public SimplexEngine::Scenes::AScene
	{
	public:
		PhysicsScene(SCENE_PARAMETERS) : SCENE_INITIALIZATION_LIST{}

		virtual void OnLoad() override;
		virtual void OnUnload() override;
		virtual void Update(float p_deltaTime) override;
	};
}

#endif // _PHYSICSSCENE_H