
#include "stdafx.h"
#include "shader.h"

namespace Core {


	Shader::Shader(const std::string filepath, const EShaderType type) {

		std::ifstream shaderFile;
		std::stringstream shaderStream;
		std::string shaderSrc;
		const char* cShaderSrc;
		int success;

		shaderFile.exceptions(shaderFile.badbit | shaderFile.failbit);
		try {
			shaderFile.open(filepath);
			shaderStream << shaderFile.rdbuf();
			shaderFile.close();
		}
		catch (std::ifstream::failure ex) {
			const char* err = ex.code().message().c_str();
			Error::Exit(std::wstring(err, err + strlen(err)));
		}

		switch (type) {
		case EShaderType::Vertex: _shader = glCreateShader(GL_VERTEX_SHADER); break;
		case EShaderType::Fragment: _shader = glCreateShader(GL_FRAGMENT_SHADER); break;
		default: std::cout << "invalid shader type"; return;
		}
		shaderSrc = shaderStream.str();
		cShaderSrc = shaderSrc.c_str();
		glShaderSource(_shader, 1, &cShaderSrc, NULL);
		glCompileShader(_shader);
		glGetShaderiv(_shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			GLint logLength;
			glGetShaderiv(_shader, GL_INFO_LOG_LENGTH, &logLength);
			std::vector<GLchar> log(logLength + 1);
			glGetShaderInfoLog(_shader, logLength, nullptr, log.data());
			std::cout << "Shader compilation failed: " << log.data() << std::endl;
			if (_shader != 0) {
				glDeleteShader(_shader);
				_shader = 0;
			}
		}

	}

	uint32_t Shader::Get() {
		return _shader;
	}

	Shader::~Shader() {
		if (_shader != 0) {
			glDeleteShader(_shader);
			_shader = 0;
		}
	}

}