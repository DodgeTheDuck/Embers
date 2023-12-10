#pragma once

namespace Core {

	class Vbo {

	public:
		void GenerateBuffer();
		void BufferData(const void* data, const uint32_t nElements, const size_t elementSize);
		void Bind();
		void Unbind();

	private:
		uint32_t _vbo;
	};

}