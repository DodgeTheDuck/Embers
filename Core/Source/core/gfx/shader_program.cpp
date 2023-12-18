#include "stdafx.h"
#include "shader_program.h"
#include "shader.h"

namespace Core {

	ShaderProgram::ShaderProgram(const std::string vertName, const std::string fragName) {

		int success;

		Shader vert = Shader("./shaders/" + vertName, EShaderType::Vertex);
		Shader frag = Shader("./shaders/" + fragName, EShaderType::Fragment);

		_shaderProg = glCreateProgram();
		glAttachShader(_shaderProg, vert.Get());
		glAttachShader(_shaderProg, frag.Get());
		glLinkProgram(_shaderProg);
		glGetProgramiv(_shaderProg, GL_LINK_STATUS, &success);
		if (!success) {
			GLint logLength;
			glGetProgramiv(_shaderProg, GL_INFO_LOG_LENGTH, &logLength);
			std::vector<GLchar> log(logLength + 1);
			glGetProgramInfoLog(_shaderProg, logLength, nullptr, log.data());
			std::cout << "shader program linking failed: " << log.data() << std::endl;
			if (_shaderProg != 0) {
				glDeleteProgram(_shaderProg);
			}
			Error::Exit(L"Failed to link shader");
		}

	}

	void ShaderProgram::Use() {
		glUseProgram(_shaderProg);
	}	

	void ShaderProgram::UniformMat4(glm::mat4 mat, const char* uniformName)
	{
		uint32_t loc = glGetUniformLocation(_shaderProg, uniformName);
		glUniformMatrix4fv(loc, 1, false, glm::value_ptr(mat));
	}

	void ShaderProgram::UniformVec3(glm::vec3 vec, const char* uniformName)
	{
		uint32_t loc = glGetUniformLocation(_shaderProg, uniformName);
		glUniform3fv(loc, 1, glm::value_ptr(vec));
	}

}