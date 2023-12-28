#include <stdafx.h>
#include "material.h"
#include "core/gl/texture.h"
#include "core/engine/engine.h"

namespace Core {

	Material::Material() {}

	Material::Material(ShaderProgram shader)
	{
		_shader = shader;
		_uni_m = _shader.GetUniformLocation("u_m");
		_uni_v = _shader.GetUniformLocation("u_v");
		_uni_p = _shader.GetUniformLocation("u_p");
		_uni_camera_pos = _shader.GetUniformLocation("u_camera_pos");
		_uni_normal_matrix = _shader.GetUniformLocation("u_normal_matrix");
		
	}

	void Material::Apply(glm::mat4 modelMatrix, MaterialProperties& properties) {

		auto& state = Gfx()->GetPipeline()->State();

		_shader.Use();
		_shader.UniformMat4(state.GetProjectionMatrix(), _uni_p);
		_shader.UniformMat4(state.GetViewMatrix(), _uni_v);
		_shader.UniformMat4(modelMatrix, _uni_m);
		_shader.UniformVec3(state.GetCameraPosition(), _uni_camera_pos);
		_shader.UniformMat3(glm::transpose(glm::inverse(glm::mat3(modelMatrix))), _uni_normal_matrix);
		
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