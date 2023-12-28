#pragma once

namespace Core {

	class Texture {
	public:
		Texture() = default;
		Texture(std::string filePath);
		Texture(void* data, uint32_t width, uint32_t height, uint32_t nChannels);
		void Bind();
		void Bind(int index);
		void Unbind();
		bool IsValid();
	private:
		int _width{};
		int _height{};
		int _nChannels{};
		bool _valid{};
		uint32_t _texture{};
	};

}