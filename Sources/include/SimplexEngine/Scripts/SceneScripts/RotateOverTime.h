/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Scripts/SceneScripts/ISceneScript.h"
#include "SimplexEngine/Actors/Actor.h"

#pragma once
#ifndef _ROTATEOVERTIME_H
#define _ROTATEOVERTIME_H

namespace SimplexEngine::Scripts::SceneScripts
{
	/**
	* Rotate an entity over time
	*/
	class RotateOverTime final : public ISceneScript
	{
	public:
		/**
		* Constructor of the script
		* @param p_target
		* @param p_rotationSpeed
		*/
		RotateOverTime(Actors::Actor& p_target, float p_rotationSpeed);

		/**
		* Update the script
		* @param p_deltaTime
		*/
		virtual void Update(float p_deltaTime) override;

	private:
		Actors::Actor& m_target;
		float m_rotationSpeed;
	};
}

#endif // _ROTATEOVERTIME_H