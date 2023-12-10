#include "stdafx.h"
#include "mesh.h"

namespace Core {

	void Mesh::FromIndices(std::vector<Vertex> vertices, std::vector<uint32_t> indices)
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

	}

}