#include <stdafx.h>
#include "material.h"

namespace Core {

	Material::Material() {}

	Material::Material(ShaderProgram shader)
	{
		_shader = shader;
	}

	void Material::Apply(Ref<GraphicsState> state, glm::mat4 modelMatrix) {
		_shader.Use();
		_shader.UniformMat4(state->GetProjectionMatrix(), "u_p");
		_shader.UniformMat4(state->GetViewMatrix(), "u_v");
		_shader.UniformMat4(modelMatrix, "u_m");
	}

}