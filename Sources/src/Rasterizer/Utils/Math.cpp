/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Utils/Math.h"

glm::quat Rasterizer::Utils::Math::CreateQuaternionFromEuler(const glm::vec3 & p_euler)
{
	const float cy = cosf(glm::radians(p_euler.z) * 0.5f);
	const float sy = sinf(glm::radians(p_euler.z) * 0.5f);
	const float cp = cosf(glm::radians(p_euler.y) * 0.5f);
	const float sp = sinf(glm::radians(p_euler.y) * 0.5f);
	const float cr = cosf(glm::radians(p_euler.x) * 0.5f);
	const float sr = sinf(glm::radians(p_euler.x) * 0.5f);

	return glm::quat
	(
		cy * cp * sr - sy * sp * cr,
		sy * cp * sr + cy * sp * cr,
		sy * cp * cr - cy * sp * sr,
		cy * cp * cr + sy * sp * sr
	);
}
