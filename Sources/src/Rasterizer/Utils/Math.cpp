/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Utils/Math.h"

glm::quat Rasterizer::Utils::Math::CreateQuaternionFromEuler(const glm::vec3 & p_euler, bool p_degrees)
{
	float yaw = p_euler.z;
	float pitch = p_euler.y;
	float roll = p_euler.x;
	
	if (p_degrees)
	{
		yaw = glm::radians(yaw);
		pitch = glm::radians(pitch);
		roll = glm::radians(roll);
	}

	float cy = cos(yaw * 0.5f);
	float sy = sin(yaw * 0.5f);
	float cp = cos(pitch * 0.5f);
	float sp = sin(pitch * 0.5f);
	float cr = cos(roll * 0.5f);
	float sr = sin(roll * 0.5f);

	return glm::quat
	(
		cy * cp * cr + sy * sp * sr,
		cy * cp * sr - sy * sp * cr,
		sy * cp * sr + cy * sp * cr,
		sy * cp * cr - cy * sp * sr
	);
}
