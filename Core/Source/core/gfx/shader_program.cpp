#include "stdafx.h"
#include "shader_program.h"
#include "shader.h"

namespace Core {

	ShaderProgram::ShaderProgram(const std::string vertName, const std::string fragName) {

		int success;

		Shader vert = Shader("./assets/shaders/" + vertName, EShaderType::Vertex);
		Shader frag = Shader("./assets/shaders/" + fragName, EShaderType::Fragment);

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

	ShaderProgram::ShaderProgram(const std::string vertName, const std::string geomName, const std::string fragName)
	{

		int success;

		Shader vert = Shader("./assets/shaders/" + vertName, EShaderType::Vertex);
		Shader frag = Shader("./assets/shaders/" + fragName, EShaderType::Fragment);
		Shader geom = Shader("./assets/shaders/" + geomName, EShaderType::Geometry);

		_shaderProg = glCreateProgram();
		glAttachShader(_shaderProg, vert.Get());
		glAttachShader(_shaderProg, frag.Get());
		glAttachShader(_shaderProg, geom.Get());
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

	int ShaderProgram::GetUniformLocation(const char* name)
	{
		return glGetUniformLocation(_shaderProg, name);
	}

	void ShaderProgram::Use() {
		glUseProgram(_shaderProg);
	}	

	void ShaderProgram::UniformMat4(glm::mat4 mat, int loc)
	{
		glUniformMatrix4fv(loc, 1, false, glm::value_ptr(mat));
	}

	void ShaderProgram::UniformMat3(const glm::mat3 mat, int loc)
	{		
		glUniformMatrix3fv(loc, 1, false, glm::value_ptr(mat));
	}

	void ShaderProgram::UniformVec3(const glm::vec3 vec, int loc)
	{		
		glUniform3fv(loc, 1, glm::value_ptr(vec));
	}

	void ShaderProgram::UniformInt(const int value, int loc)
	{		
		glUniform1i(loc, value);
	}

	void ShaderProgram::UniformUInt(const unsigned int value, int loc)
	{		
		glUniform1ui(loc, value);
	}

	void ShaderProgram::UniformFloat(const float value, int loc)
	{		
		glUniform1f(loc, value);
	}

}