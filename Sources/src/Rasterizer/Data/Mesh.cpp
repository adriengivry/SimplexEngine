/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Data/Mesh.h"
#include "Rasterizer/Utils/EasyAssimp.h"

Rasterizer::Data::Mesh::Mesh()
{
}

Rasterizer::Data::Mesh::Mesh(const std::string & p_filename)
{
	Utils::EasyAssimp::LoadVertices(p_filename, m_vertices, m_indices);
}

Rasterizer::Data::Mesh::Mesh(std::vector<Vertex>& p_vertices)
{
	m_vertices = p_vertices;
}

Rasterizer::Data::Mesh::Mesh(EPrimitive p_primitive)
{
	switch (p_primitive)
	{
	case EPrimitive::CUBE:
		MakeCube();
		break;
	}
}

void Rasterizer::Data::Mesh::MakeCube()
{
	m_vertices.clear();
	m_indices.clear();

	AddVertex({ 0.5, 0.5, -0.5 }); //2 0 
	AddVertex({ -0.5, 0.5, -0.5 }); //3 1
	AddVertex({ -0.5, -0.5, -0.5 }); //0 2
	AddVertex({ 0.5, 0.5, -0.5 }); //2   3
	AddVertex({ -0.5, -0.5, -0.5 }); //0  4
	AddVertex({ 0.5, -0.5, -0.5 }); //1  5
	AddVertex({ 0.5, 0.5, 0.5 }); //6     6
	AddVertex({ 0.5, 0.5, -0.5 }); //2   7
	AddVertex({ 0.5, -0.5, -0.5 }); //1      8
	AddVertex({ 0.5, 0.5, 0.5 }); //6     9
	AddVertex({ 0.5, -0.5, -0.5 }); //1      10
	AddVertex({ 0.5, -0.5, 0.5 }); //5    11
	AddVertex({ -0.5, 0.5, 0.5 }); //7   12
	AddVertex({ 0.5, 0.5, 0.5 }); //6    13
	AddVertex({ 0.5, -0.5, 0.5 }); //5    14
	AddVertex({ -0.5, 0.5, 0.5 }); //7   15
	AddVertex({ 0.5, -0.5, 0.5 }); //5    16
	AddVertex({ -0.5, -0.5, 0.5 }); //4  17
	AddVertex({ -0.5, 0.5, -0.5 }); //3  18
	AddVertex({ -0.5, 0.5, 0.5 }); //7   19
	AddVertex({ -0.5, -0.5, 0.5 }); //4  20
	AddVertex({ -0.5, 0.5, -0.5 }); //3  21
	AddVertex({ -0.5, -0.5, 0.5 }); //4  22
	AddVertex({ -0.5, -0.5, -0.5 }); //0  23
	AddVertex({ -0.5, 0.5, -0.5 }); //3  24
	AddVertex({ 0.5, 0.5, -0.5 }); //2   25
	AddVertex({ 0.5, 0.5, 0.5 }); //6     26
	AddVertex({ -0.5, 0.5, -0.5 }); //3  27
	AddVertex({ 0.5, 0.5, 0.5 }); //6     28
	AddVertex({ -0.5, 0.5, 0.5 }); //7   29
	AddVertex({ -0.5, -0.5, 0.5 }); //4   30
	AddVertex({ 0.5, -0.5, 0.5 }); //5    31
	AddVertex({ 0.5, -0.5, -0.5 }); //1      32
	AddVertex({ -0.5, -0.5, 0.5 }); //4   33
	AddVertex({ 0.5, -0.5, -0.5 }); //1      34
	AddVertex({ -0.5, -0.5, -0.5 }); //0  35
}

void Rasterizer::Data::Mesh::AddVertex(const Vertex& p_vertex, bool p_autoIndex)
{
	m_vertices.push_back(p_vertex);
	if (p_autoIndex)
		m_indices.push_back(m_indices.empty() ? 0 : m_indices[m_indices.size() - 1] + 1);
}

void Rasterizer::Data::Mesh::AddIndice(uint32_t p_indice)
{
	m_indices.push_back(p_indice);
}

const std::vector<Rasterizer::Data::Vertex>& Rasterizer::Data::Mesh::GetVertices() const
{
	return m_vertices;
}

const std::vector<uint32_t>& Rasterizer::Data::Mesh::GetIndices() const
{
	return m_indices;
}
