#include "stdafx.h"
#include "vbo.h"

namespace Core {

	void Vbo::GenerateBuffer() {
		if (_vbo != 0) {
			Error::Exit(L"Buffer already generated");
		}
		glGenBuffers(1, &_vbo);
	}

	void Vbo::BufferData(const void* data, const uint32_t nElements, const size_t elementSize) {
		if (_vbo == 0) {
			Error::Exit(L"Trying to add data to invalid buffer");
		}
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, nElements * elementSize, data, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Vbo::Bind() {
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	}

	void Vbo::Unbind() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}