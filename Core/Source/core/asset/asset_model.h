#pragma once

#include "core/asset/asset.h"
#include "core/gfx/model.h"
#include "dll.h"

namespace Core {
	class ENGINE_API AssetModel : public Asset {
	public:
		AssetModel() = default;
		AssetModel(std::vector<Mesh> meshes, Material material) : _meshes(meshes), _material(material) {};

		std::vector<Mesh> GetMeshes();
		Material GetMaterial();

	private:
		std::vector<Mesh> _meshes;
		Material _material;
	};
}