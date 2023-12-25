#pragma once

#include <dll.h>
#include <core/geometry/mesh.h>

namespace Core {

	class ENGINE_API Model {

	public:
		Model();
		Model(std::vector<Mesh> meshes, Material material);

		Material GetMaterial();
		std::vector<Mesh> GetMeshes();

	protected:
		std::vector<Mesh> _meshes{};
		Material _material;

	};

}