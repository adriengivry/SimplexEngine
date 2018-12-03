/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Resources/Mesh.h"
#include "Rasterizer/Tools/EasyAssimp.h"

Rasterizer::Resources::Mesh::Mesh(const std::string & p_filename)
{
	Tools::EasyAssimp::LoadVertices(p_filename, m_vertices, m_indices);
}

void Rasterizer::Resources::Mesh::AddVertex(const Data::Vertex& p_vertex, bool p_autoIndex)
{
	m_vertices.push_back(p_vertex);
	if (p_autoIndex)
		m_indices.push_back(m_indices.empty() ? 0 : m_indices[m_indices.size() - 1] + 1);
}

void Rasterizer::Resources::Mesh::AddIndice(uint32_t p_indice)
{
	m_indices.push_back(p_indice);
}

void Rasterizer::Resources::Mesh::ClearData()
{
	m_vertices.clear();
	m_indices.clear();
}

const std::vector<Rasterizer::Data::Vertex>& Rasterizer::Resources::Mesh::GetVertices() const
{
	return m_vertices;
}

const std::vector<uint32_t>& Rasterizer::Resources::Mesh::GetIndices() const
{
	return m_indices;
}
