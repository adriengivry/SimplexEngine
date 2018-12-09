/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Data/Vertex.h"

SimplexEngine::Data::Vertex::Vertex(float p_x, float p_y, float p_z, float p_nx, float p_ny, float p_nz) :
	position(p_x, p_y, p_z),
	normal(p_nx, p_ny, p_nz)
{
}
