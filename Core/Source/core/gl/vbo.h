#pragma once

namespace Core {

	class Vbo {

	public:
		void GenerateBuffer();
		void BufferData(const void* data, const size_t nElements, const size_t elementSize);
		void Bind();
		void Unbind();
		void Delete();

		bool IsValid();

	private:
		uint32_t _vbo{};
	};

}