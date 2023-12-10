#include "stdafx.h"
#include "ebo.h"

namespace Core {

	void Ebo::GenerateBuffer() {
		if (_ebo != 0) {
			Error::Exit(L"Buffer already generated");
		}
		glGenBuffers(1, &_ebo);
	}

	void Ebo::BufferData(std::vector<uint32_t> indices) {
		if (_ebo == 0) {
			Error::Exit(L"Trying to add data to invalid buffer");
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void Ebo::Bind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	}

	void Ebo::Unbind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}