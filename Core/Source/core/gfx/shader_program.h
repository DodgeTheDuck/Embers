#pragma once

namespace Core {

	class ShaderProgram {

	public:
		ShaderProgram() = default;
		ShaderProgram(const std::string vertName, const std::string fragName);

		void UniformMat4(const glm::mat4 mat, const char* uniformName);
		void UniformVec3(const glm::vec3 vec, const char* uniformName);

		void Use();

	private:
		unsigned int _shaderProg;

	};

}