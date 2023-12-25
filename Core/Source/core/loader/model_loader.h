#pragma once

#include "core/gfx/model.h"

namespace Core {

	class ModelLoader {
	public:
		ModelLoader() = default;
		Ref<Model> Load(std::string filePath);

	private:

		Mesh _ParseMesh(aiMesh* mesh, const aiScene* scene);
		MaterialProperties _ParseMaterialProperties(aiMaterial* material, const aiScene* scene);
		std::unordered_map<MaterialTextureType, Texture> _ParseTextures(aiMaterial* material, const aiScene* scene);
		Texture _LoadTexture(aiTextureType type, aiMaterial* material, const aiScene* scene);
		

	};

}