#pragma once

#include "vertex.h"
#include "gl/vbo.h"
#include "gl/vao.h"
#include "gl/ebo.h"

namespace Core {

	class Mesh {
	public:
		void FromIndices(std::vector<Vertex> vertices, std::vector<uint32_t> indices);
	private:

		Vbo _vbo;
		Vao _vao;
		Ebo _ebo;

	};

}