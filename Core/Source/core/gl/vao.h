#pragma once

namespace Core {

	class Vao {

	public:
		void GenerateBuffer();
		void VertexAttribPointer(uint32_t index, uint32_t size, uint32_t type, uint32_t stride, void * pointer);
		void VertexAttribDivisor(uint32_t location, uint32_t divisor);
		void Bind();
		void Unbind();

	private:
		uint32_t _vao;

	};

}