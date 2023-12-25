#include "stdafx.h"
#include "vao.h"

namespace Core {

	void Vao::GenerateBuffer() {
		if (_vao != 0) {
			Error::Exit(L"Buffer already generated");
		}
		glGenVertexArrays(1, &_vao);
	}

	void Vao::VertexAttribPointer(uint32_t index, uint32_t size, uint32_t type, size_t stride, void * pointer) {
		glVertexAttribPointer(index, size, type, GL_FALSE, (GLsizei)stride, pointer);
		glEnableVertexAttribArray(index);
	}

	void Vao::VertexAttribDivisor(uint32_t location, uint32_t divisor) {
		glVertexAttribDivisor(location, divisor);
	}

	void Vao::Bind() {
		glBindVertexArray(_vao);
	}

	void Vao::Unbind() {
		glBindVertexArray(0);
	}

}