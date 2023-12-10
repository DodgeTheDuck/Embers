#pragma once

namespace Core {

	class Ebo {

	public:
		void GenerateBuffer();
		void BufferData(std::vector<uint32_t> indices);

		void Bind();
		void Unbind();

	private:
		uint32_t _ebo{};

	};

}