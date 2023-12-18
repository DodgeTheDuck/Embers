#pragma once

#include <dll.h>
#include "shader_program.h"
#include "graphics_state.h"

namespace Core {

	class ENGINE_API Material {

	public:
		Material();
		Material(ShaderProgram shader);
		void Apply(Ref<GraphicsState> state, glm::mat4 modelMatrix);

	private:
		ShaderProgram _shader;

	};

}