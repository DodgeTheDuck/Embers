#include <stdafx.h>
#include <core/geometry/mesh.h>

namespace Core {

	Mesh::Mesh()
	{
	}

	Mesh::Mesh(Primitive& primitive)
	{
		_Make(primitive.GetVertices(), primitive.GetIndices());
	}

	void Mesh::Bind()
	{
		_vao.Bind();
	}

	uint32_t Mesh::VertCount()
	{
		return _nVerts;
	}

	uint32_t Mesh::IndexCount()
	{
		return _nIndices;
	}

	void Mesh::_Make(std::vector<Vertex> vertices, std::vector<uint32_t> indices)
	{

		_vao.GenerateBuffer();
		_vbo.GenerateBuffer();
		_ebo.GenerateBuffer();

		_vbo.BufferData(vertices.data(), vertices.size(), sizeof(Vertex));
		_ebo.BufferData(indices);

		_vao.Bind();
		_vbo.Bind();
		_ebo.Bind();

		_vao.VertexAttribPointer(0, 3, GL_FLOAT, sizeof(float) * 6, (void*)0);

		_vao.Unbind();
		_vbo.Unbind();
		_ebo.Unbind();

		_nVerts = vertices.size();
		_nIndices = indices.size();

	}

}