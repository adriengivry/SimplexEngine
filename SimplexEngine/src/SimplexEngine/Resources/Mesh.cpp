/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Resources/Mesh.h"
#include "SimplexEngine/Utils/EasyAssimp.h"

SimplexEngine::Resources::Mesh::Mesh(const std::string & p_filename)
{
	Utils::EasyAssimp::LoadVertices(p_filename, m_vertices, m_indices);
}

void SimplexEngine::Resources::Mesh::AddVertex(const Data::Vertex& p_vertex, bool p_autoIndex)
{
	m_vertices.push_back(p_vertex);
	if (p_autoIndex)
		m_indices.push_back(m_indices.empty() ? 0 : m_indices[m_indices.size() - 1] + 1);
}

void SimplexEngine::Resources::Mesh::AddIndice(uint32_t p_indice)
{
	m_indices.push_back(p_indice);
}

void SimplexEngine::Resources::Mesh::ClearData()
{
	m_vertices.clear();
	m_indices.clear();
}

const std::vector<SimplexEngine::Data::Vertex>& SimplexEngine::Resources::Mesh::GetVertices() const
{
	return m_vertices;
}

const std::vector<uint32_t>& SimplexEngine::Resources::Mesh::GetIndices() const
{
	return m_indices;
}
