#include "Rasterizer/Data/Mesh.h"

Rasterizer::Data::Mesh::Mesh()
{
}

Rasterizer::Data::Mesh::Mesh(std::vector<Vertex>& p_vertices)
{
	m_vertices = p_vertices;
}

void Rasterizer::Data::Mesh::AddVertex(const Vertex& p_vertex)
{
	m_vertices.push_back(p_vertex);
}

const std::vector<Rasterizer::Data::Vertex>& Rasterizer::Data::Mesh::GetVertices() const
{
	return m_vertices;
}
