#include "Rasterizer/Utils/Math.h"

AltMath::Quaternion Rasterizer::Utils::Math::CreateQuaternionFromEuler(const AltMath::Vector3f & p_euler)
{
	const float cy = AltMath::Tools::Utils::CosF(AltMath::Tools::Utils::ToRadians(p_euler.z) * 0.5f);
	const float sy = AltMath::Tools::Utils::SinF(AltMath::Tools::Utils::ToRadians(p_euler.z) * 0.5f);
	const float cp = AltMath::Tools::Utils::CosF(AltMath::Tools::Utils::ToRadians(p_euler.y) * 0.5f);
	const float sp = AltMath::Tools::Utils::SinF(AltMath::Tools::Utils::ToRadians(p_euler.y) * 0.5f);
	const float cr = AltMath::Tools::Utils::CosF(AltMath::Tools::Utils::ToRadians(p_euler.x) * 0.5f);
	const float sr = AltMath::Tools::Utils::SinF(AltMath::Tools::Utils::ToRadians(p_euler.x) * 0.5f);

	return AltMath::Quaternion
	(
		cy * cp * sr - sy * sp * cr,
		sy * cp * sr + cy * sp * cr,
		sy * cp * cr - cy * sp * sr,
		cy * cp * cr + sy * sp * sr
	);
}
