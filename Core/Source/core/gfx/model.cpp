#include <stdafx.h>
#include <core/gfx/model.h>

namespace Core {

	Model::Model()
	{

	}

	Model::Model(std::vector<Mesh> meshes, Ref<Material> material)
	{
		_meshes = meshes;
		_material = material;
	}

	Ref<Material> Model::GetMaterial()
	{
		return _material;
	}

	std::vector<Mesh> Model::Meshes()
	{
		return _meshes;
	}

}
