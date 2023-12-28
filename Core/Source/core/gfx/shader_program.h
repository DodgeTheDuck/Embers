#pragma once

namespace Core {

	class ShaderProgram {

	public:
		ShaderProgram() = default;
		ShaderProgram(const std::string vertName, const std::string fragName);
		ShaderProgram(const std::string vertName, const std::string geomName, const std::string fragName);

		int GetUniformLocation(const char* name);

		void UniformMat4(const glm::mat4 mat, int loc);
		void UniformMat3(const glm::mat3 mat, int loc);
		void UniformVec3(const glm::vec3 vec, int loc);
		void UniformInt(const int value, int loc);
		void UniformUInt(const unsigned int value, int loc);
		void UniformFloat(const float value, int loc);

		void Use();

	private:
		unsigned int _shaderProg;

	};

}