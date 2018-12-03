/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Scripts/IScript.h"
#include "Rasterizer/Entities/AEntity.h"

#pragma once
#ifndef _SROTATEOVERTIME_H
#define _SROTATEOVERTIME_H

namespace Rasterizer::Scripts
{
	/**
	* Rotate an entity over time
	*/
	class SRotateOverTime final : public IScript
	{
	public:
		/**
		* Constructor of the script
		* @param p_target
		* @param p_rotationSpeed
		*/
		SRotateOverTime(Entities::AEntity& p_target, float p_rotationSpeed);

		/**
		* Update the script
		* @param p_deltaTime
		*/
		virtual void Update(float p_deltaTime) override;

	private:
		Entities::AEntity& m_target;
		float m_rotationSpeed;
		float m_rotationAngle;

	};
}

#endif // _SROTATEOVERTIME_H