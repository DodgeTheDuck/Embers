#pragma once

#include <core/geometry/vertex.h>
#include <core/gl/vbo.h>
#include <core/gl/vao.h>
#include <core/gl/ebo.h>
#include <core/geometry/primitive.h>
#include <core/gfx/material.h>
#include <dll.h>

namespace Core {

	class ENGINE_API Mesh {
	public:
		Mesh();
		Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, MaterialProperties properties);
		Mesh(Primitive& primitive);

		void Bind();

		Vao GetVao();
		Vbo GetVbo();
		Ebo GetEbo();

		MaterialProperties& Properties();

		uint32_t VertCount();
		uint32_t IndexCount();
		
	private:
		void _Make(std::vector<Vertex> vertices, std::vector<uint32_t> indices, MaterialProperties properties);

		uint32_t _nVerts{};
		uint32_t _nIndices{};

		Vbo _vbo{};
		Vao _vao{};
		Ebo _ebo{};

		MaterialProperties _materialProperties;

	};

}