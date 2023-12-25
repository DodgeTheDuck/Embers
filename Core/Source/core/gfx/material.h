#pragma once

#include <dll.h>
#include "shader_program.h"
#include "graphics_state.h"
#include "core/gl/texture.h"

namespace Core {

	enum MaterialTextureType {
		ALBEDO,
		NORMAL,
		METALLIC,
		ROUGHNESS,
		METALLIC_ROUGHNESS,
		AMBIENT_OCCLUSION
	};

	struct MaterialProperties {
		std::unordered_map<MaterialTextureType, Texture> textures;
	};

	class ENGINE_API Material {

	public:
		Material();
		Material(ShaderProgram shader);
		void Apply(Ref<GraphicsState> state, glm::mat4 modelMatrix, MaterialProperties& properties);

	private:
		ShaderProgram _shader;

	};

}