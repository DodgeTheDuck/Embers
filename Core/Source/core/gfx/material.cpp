#include <stdafx.h>
#include "material.h"
#include "core/gl/texture.h"

namespace Core {

	Material::Material() {}

	Material::Material(ShaderProgram shader)
	{
		_shader = shader;
	}

	void Material::Apply(Ref<GraphicsState> state, glm::mat4 modelMatrix, MaterialProperties& properties) {
		_shader.Use();
		_shader.UniformMat4(state->GetProjectionMatrix(), "u_p");
		_shader.UniformMat4(state->GetViewMatrix(), "u_v");
		_shader.UniformMat4(modelMatrix, "u_m");
		_shader.UniformVec3(state->GetCameraPosition(), "u_camera_pos");
		_shader.UniformMat3(glm::transpose(glm::inverse(glm::mat3(modelMatrix))), "u_normal_matrix");
		
		if (properties.textures[MaterialTextureType::ALBEDO].IsValid()) {
			glActiveTexture(GL_TEXTURE0 + 0);
			properties.textures[MaterialTextureType::ALBEDO].Bind();			
		}

		if (properties.textures[MaterialTextureType::NORMAL].IsValid()) {
			glActiveTexture(GL_TEXTURE0 + 1);
			properties.textures[MaterialTextureType::NORMAL].Bind();		
		}

		if (properties.textures[MaterialTextureType::METALLIC].IsValid()) {
			glActiveTexture(GL_TEXTURE0 + 2);
			properties.textures[MaterialTextureType::METALLIC].Bind();			
		}

		if (properties.textures[MaterialTextureType::ROUGHNESS].IsValid()) {
			glActiveTexture(GL_TEXTURE0 + 3);
			properties.textures[MaterialTextureType::ROUGHNESS].Bind();			
		}
		
		if (properties.textures[MaterialTextureType::METALLIC_ROUGHNESS].IsValid()) {
			glActiveTexture(GL_TEXTURE0 + 4);
			properties.textures[MaterialTextureType::METALLIC_ROUGHNESS].Bind();			
		}

		if (properties.textures[MaterialTextureType::AMBIENT_OCCLUSION].IsValid()) {
			glActiveTexture(GL_TEXTURE0 + 5);
			properties.textures[MaterialTextureType::AMBIENT_OCCLUSION].Bind();			
		}

	}

}