/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _QUATERNIONFACTORY_H
#define _QUATERNIONFACTORY_H

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "SimplexEngine/API/Export.h"

namespace SimplexEngine::Maths
{
	/**
	* Contains some static math tools
	*/
	class API_SIMPLEXENGINE QuaternionFactory final
	{
	public:
		/* Prevent this static class from being instancied */
		QuaternionFactory() = delete;

		/**
		* Create a quaternion from euler
		* @param p_euler
		* @param p_degrees (True to use degrees and false to use radians)
		*/
		static glm::quat CreateFromEuler(const glm::vec3& p_euler, bool p_degrees = true);
	};
}

#endif // _MATH_H