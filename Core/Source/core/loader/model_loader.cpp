#include "stdafx.h"
#include "model_loader.h"
#include "core/engine/engine.h"
#include "core/asset/asset_shader.h"
#include "stb_image.h"

namespace Core {

	Ref<Model> ModelLoader::Load(std::string filePath)
	{

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile("./assets/models/" + filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			Error::Exit(L"Unable to load model");
		}

		if (scene->HasMeshes()) {

			std::vector<Mesh> meshes;

			for (int i = 0; i < scene->mNumMeshes; i++) {
				const auto& sceneMesh = scene->mMeshes[i];
				meshes.push_back(_ParseMesh(sceneMesh, scene));
			}

			return CreateRef<Model>(meshes, Material(ASSETS()->CopyAsset<AssetShader>("shader_model")));

		}

		return nullptr;


	}

	Mesh ModelLoader::_ParseMesh(aiMesh* mesh, const aiScene* scene)
	{

		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;

		for (int j = 0; j < mesh->mNumVertices; j++) {
			auto vertex = mesh->mVertices[j];
			auto normal = mesh->mNormals[j];
			auto uv = mesh->mTextureCoords[0][j];
			auto v = Vertex();
			v.Position = glm::vec3(vertex.x, vertex.y, vertex.z);
			v.Color = glm::vec3(1.0, 1.0, 1.0);
			v.UV = glm::vec2(uv.x, uv.y);
			v.Normal = glm::vec3(normal.x, normal.y, normal.z);
			vertices.push_back(v);
		}

		for (int j = 0; j < mesh->mNumFaces; j++) {
			auto face = mesh->mFaces[j];
			for (int k = 0; k < face.mNumIndices; k++) {
				indices.push_back(face.mIndices[k]);
			}
		}

		auto materialProperties = _ParseMaterialProperties(scene->mMaterials[mesh->mMaterialIndex], scene);

		return Mesh(vertices, indices, materialProperties);

	}

	MaterialProperties ModelLoader::_ParseMaterialProperties(aiMaterial* material, const aiScene* scene)
	{
		auto p = MaterialProperties();
		p.textures = _ParseTextures(material, scene);		
		return p;
	}

	std::unordered_map<MaterialTextureType, Texture> ModelLoader::_ParseTextures(aiMaterial* material, const aiScene* scene) {

		return {
			{MaterialTextureType::ALBEDO, _LoadTexture(aiTextureType_DIFFUSE, material, scene)},
			{MaterialTextureType::NORMAL, _LoadTexture(aiTextureType_NORMALS, material, scene)},
			{MaterialTextureType::METALLIC, _LoadTexture(aiTextureType_METALNESS, material, scene)},
			{MaterialTextureType::ROUGHNESS, _LoadTexture(aiTextureType_DIFFUSE_ROUGHNESS, material, scene)},
			{MaterialTextureType::METALLIC_ROUGHNESS, _LoadTexture(aiTextureType_UNKNOWN, material, scene)},
			{MaterialTextureType::AMBIENT_OCCLUSION, _LoadTexture(aiTextureType_LIGHTMAP, material, scene)},
		};
	}

	Texture ModelLoader::_LoadTexture(aiTextureType type, aiMaterial* material, const aiScene* scene)
	{
		aiString texturePath;
		if (AI_SUCCESS == material->GetTexture(type, 0, &texturePath)) {
			if (auto texture = scene->GetEmbeddedTexture(texturePath.C_Str())) {
				int texWidth{};
				int texHeight{};
				int texChannels{};
				unsigned char* imageData{};
				if (texture->mHeight == 0) {
					imageData = stbi_load_from_memory(reinterpret_cast<unsigned char*>(texture->pcData), texture->mWidth, &texWidth, &texHeight, &texChannels, 0);				
				}
				else {
					imageData = stbi_load_from_memory(reinterpret_cast<unsigned char*>(texture->pcData), texture->mWidth * texture->mHeight, &texWidth, &texHeight, &texChannels, 0);
				}
				return Texture(imageData, texWidth, texHeight, texChannels);				
			}
		}
		return Texture();
	}

}