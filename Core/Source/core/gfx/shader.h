#pragma once

namespace Core {

	enum EShaderType {
		None = 0,
		Vertex = 1,
		Fragment = 2,
	};

	class Shader {

	public:
		Shader(const std::string filepath, const EShaderType type);
		uint32_t Get();
		~Shader();

	private:
		unsigned int _shader{};
	};

}