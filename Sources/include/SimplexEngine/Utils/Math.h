/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _MATH_H
#define _MATH_H

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace SimplexEngine::Utils
{
	/**
	* Contains some static math tools
	*/
	class Math final
	{
	public:
		/* Prevent this static class from being instancied */
		Math() = delete;

		/**
		* Create a quaternion from euler
		* @param p_euler
		* @param p_degrees (True to use degrees and false to use radians)
		*/
		static glm::quat CreateQuaternionFromEuler(const glm::vec3& p_euler, bool p_degrees = true);
	};
}

#endif // _MATH_H