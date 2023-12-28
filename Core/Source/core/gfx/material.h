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
		void Apply(glm::mat4 modelMatrix, MaterialProperties& properties);

	private:
		ShaderProgram _shader;

		int _uni_m;
		int _uni_v;
		int _uni_p;
		int _uni_camera_pos;
		int _uni_normal_matrix;

	};

}