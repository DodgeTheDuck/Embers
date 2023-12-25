#include <stdafx.h>
#include <core/gfx/model.h>

namespace Core {

	Model::Model()
	{

	}

	Model::Model(std::vector<Mesh> meshes, Material material)
	{
		_meshes = meshes;
		_material = material;
	}

	Material Model::GetMaterial()
	{
		return _material;
	}

	std::vector<Mesh> Model::GetMeshes()
	{
		return _meshes;
	}

}
