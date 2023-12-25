#include "stdafx.h"
#include "asset_model.h"

namespace Core {

	std::vector<Mesh> AssetModel::GetMeshes()
	{
		return _meshes;
	}

	Material AssetModel::GetMaterial() {
		return _material;
	}

}