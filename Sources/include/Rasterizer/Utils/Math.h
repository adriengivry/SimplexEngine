/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _MATH_H
#define _MATH_H

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Rasterizer::Utils
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
		*/
		static glm::quat CreateQuaternionFromEuler(const glm::vec3& p_euler);
	};
}

#endif // _MATH_H