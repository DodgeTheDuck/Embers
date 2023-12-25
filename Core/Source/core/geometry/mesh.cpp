#include <stdafx.h>
#include <core/geometry/mesh.h>

namespace Core {

	Mesh::Mesh()
	{
	}

	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, MaterialProperties properties)
	{
		_Make(vertices, indices, properties);
	}

	Mesh::Mesh(Primitive& primitive)
	{
		_Make(primitive.GetVertices(), primitive.GetIndices(), primitive.Properties());
	}

	void Mesh::Bind()
	{
		_vao.Bind();
	}

	Vao Mesh::GetVao()
	{
		return _vao;
	}

	Vbo Mesh::GetVbo()
	{
		return _vbo;
	}

	Ebo Mesh::GetEbo()
	{
		return _ebo;
	}

	MaterialProperties& Mesh::Properties()
	{
		return _materialProperties;
	}

	uint32_t Mesh::VertCount()
	{
		return _nVerts;
	}

	uint32_t Mesh::IndexCount()
	{
		return _nIndices;
	}

	void Mesh::_Make(std::vector<Vertex> vertices, std::vector<uint32_t> indices, MaterialProperties properties)
	{

		_vao.GenerateBuffer();
		_vbo.GenerateBuffer();
		_ebo.GenerateBuffer();

		_vbo.BufferData(vertices.data(), vertices.size(), sizeof(Vertex));
		_ebo.BufferData(indices);

		_vao.Bind();
		_vbo.Bind();
		_ebo.Bind();

		/* pos */ _vao.VertexAttribPointer(0, 3, GL_FLOAT, sizeof(float) * 11, (void*)0);
		/* col */ _vao.VertexAttribPointer(1, 3, GL_FLOAT, sizeof(float) * 11, (void*)(sizeof(float) * 3));
		/* uvs */ _vao.VertexAttribPointer(2, 2, GL_FLOAT, sizeof(float) * 11, (void*)(sizeof(float) * 6));
		/* nrm */ _vao.VertexAttribPointer(3, 3, GL_FLOAT, sizeof(float) * 11, (void*)(sizeof(float) * 8));

		_vao.Unbind();
		_vbo.Unbind();
		_ebo.Unbind();

		_nVerts = vertices.size();
		_nIndices = indices.size();
		_materialProperties = properties;

	}

}