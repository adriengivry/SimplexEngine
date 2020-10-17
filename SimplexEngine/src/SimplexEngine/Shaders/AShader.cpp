/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Shaders/AShader.h"
#include "SimplexEngine/Analytics/ProfilerSpy.h"

glm::vec4 SimplexEngine::Shaders::AShader::ProcessVertex(const Data::Vertex & p_vertex, uint8_t p_vertexID)
{
	PROFILER_SPY("AShader::ProcessVertex");

	m_index = p_vertexID;
	return VertexModifier(p_vertex);
}

SimplexEngine::Data::Color SimplexEngine::Shaders::AShader::ProcessFragment()
{
	PROFILER_SPY("AShader::ProcessFragment");

	return FragmentModifier();
}

void SimplexEngine::Shaders::AShader::ProcessInterpolation(const glm::vec3& p_barycentricCoords)
{
	PROFILER_SPY("AShader::ProcessInterpolation");

    /*
    for (int i = 0; i < 128; ++i)
    {
        m_interpolatedVarying[i] =
            m_varying[i][0] * p_barycentricCoords.z +
            m_varying[i][1] * p_barycentricCoords.y +
            m_varying[i][2] * p_barycentricCoords.x;
    }
    */
    // Load barycentric coordinates in xmm register
    __m128 bcx = _mm_broadcast_ss(&p_barycentricCoords.x);
    __m128 bcy = _mm_broadcast_ss(&p_barycentricCoords.y);
    __m128 bcz = _mm_broadcast_ss(&p_barycentricCoords.z);

    for (int i = 0; i < m_lastVaryingIndex; ++i)
    {
        // Load the three vertex varings into xmm registers
        __m128 v0 = _mm_load_ps(&m_varying[i][0].x);
        __m128 v1 = _mm_load_ps(&m_varying[i][1].x);
        __m128 v2 = _mm_load_ps(&m_varying[i][2].x);

        // Interpolation result
        __m128 result = 
            _mm_add_ps(
                _mm_add_ps(
                    _mm_mul_ps(v0, bcz),
                    _mm_mul_ps(v1, bcy)),
                _mm_mul_ps(v2, bcx)
            );



        // Store interpolation result
        _mm_store_ps(&m_interpolatedVarying[i].x, result);
    }
}

void SimplexEngine::Shaders::AShader::ClearData()
{
    m_lastVaryingIndex = 0;
}
