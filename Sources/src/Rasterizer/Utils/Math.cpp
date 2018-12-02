#include "Rasterizer/Utils/Math.h"

float Rasterizer::Utils::Math::ToRadians(float p_value)
{
	return p_value * 3.14f / 180.0f;
}

glm::quat Rasterizer::Utils::Math::CreateQuaternionFromEuler(const glm::vec3 & p_euler)
{
	const float cy = cosf(ToRadians(p_euler.z) * 0.5f);
	const float sy = sinf(ToRadians(p_euler.z) * 0.5f);
	const float cp = cosf(ToRadians(p_euler.y) * 0.5f);
	const float sp = sinf(ToRadians(p_euler.y) * 0.5f);
	const float cr = cosf(ToRadians(p_euler.x) * 0.5f);
	const float sr = sinf(ToRadians(p_euler.x) * 0.5f);

	return glm::quat
	(
		cy * cp * sr - sy * sp * cr,
		sy * cp * sr + cy * sp * cr,
		sy * cp * cr - cy * sp * sr,
		cy * cp * cr + sy * sp * sr
	);
}
