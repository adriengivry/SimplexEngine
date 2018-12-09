/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Tools/MeshCreator.h"

void SimplexEngine::Tools::MeshCreator::CreateCube(Resources::Mesh & p_outMesh)
{
	p_outMesh.ClearData();

	p_outMesh.AddVertex({ 1.0f, 1.0f, -1.0f, }); //2 0 
	p_outMesh.AddVertex({ -1.0f, 1.0f, -1.0f }); //3 1
	p_outMesh.AddVertex({ -1.0f, -1.0f, -1.0f }); //0 2
	p_outMesh.AddVertex({ 1.0f, 1.0f, -1.0f }); //2   3
	p_outMesh.AddVertex({ -1.0f, -1.0f, -1.0f }); //0  4
	p_outMesh.AddVertex({ 1.0f, -1.0f, -1.0f }); //1  5
	p_outMesh.AddVertex({ 1.0f, 1.0f, 1.0f }); //6     6
	p_outMesh.AddVertex({ 1.0f, 1.0f, -1.0f }); //2   7
	p_outMesh.AddVertex({ 1.0f, -1.0f, -1.0f }); //1      8
	p_outMesh.AddVertex({ 1.0f, 1.0f, 1.0f }); //6     9
	p_outMesh.AddVertex({ 1.0f, -1.0f, -1.0f }); //1      10
	p_outMesh.AddVertex({ 1.0f, -1.0f, 1.0f }); //5    11
	p_outMesh.AddVertex({ -1.0f, 1.0f, 1.0f }); //7   12
	p_outMesh.AddVertex({ 1.0f, 1.0f, 1.0f }); //6    13
	p_outMesh.AddVertex({ 1.0f, -1.0f, 1.0f }); //5    14
	p_outMesh.AddVertex({ -1.0f, 1.0f, 1.0f }); //7   15
	p_outMesh.AddVertex({ 1.0f, -1.0f, 1.0f }); //5    16
	p_outMesh.AddVertex({ -1.0f, -1.0f, 1.0f }); //4  17
	p_outMesh.AddVertex({ -1.0f, 1.0f, -1.0f }); //3  18
	p_outMesh.AddVertex({ -1.0f, 1.0f, 1.0f }); //7   19
	p_outMesh.AddVertex({ -1.0f, -1.0f, 1.0f }); //4  20
	p_outMesh.AddVertex({ -1.0f, 1.0f, -1.0f }); //3  21
	p_outMesh.AddVertex({ -1.0f, -1.0f, 1.0f }); //4  22
	p_outMesh.AddVertex({ -1.0f, -1.0f, -1.0f }); //0  23
	p_outMesh.AddVertex({ -1.0f, 1.0f, -1.0f }); //3  24
	p_outMesh.AddVertex({ 1.0f, 1.0f, -1.0f }); //2   25
	p_outMesh.AddVertex({ 1.0f, 1.0f, 1.0f }); //6     26
	p_outMesh.AddVertex({ -1.0f, 1.0f, -1.0f }); //3  27
	p_outMesh.AddVertex({ 1.0f, 1.0f, 1.0f }); //6     28
	p_outMesh.AddVertex({ -1.0f, 1.0f, 1.0f }); //7   29
	p_outMesh.AddVertex({ -1.0f, -1.0f, 1.0f }); //4   30
	p_outMesh.AddVertex({ 1.0f, -1.0f, 1.0f }); //5    31
	p_outMesh.AddVertex({ 1.0f, -1.0f, -1.0f }); //1      32
	p_outMesh.AddVertex({ -1.0f, -1.0f, 1.0f }); //4   33
	p_outMesh.AddVertex({ 1.0f, -1.0f, -1.0f }); //1      34
	p_outMesh.AddVertex({ -1.0f, -1.0f, -1.0f }); //0  35
}
