#pragma once

#include <dll.h>
#include <core/geometry/mesh.h>

namespace Core {

	class ENGINE_API Model {

	public:
		Model();
		Model(std::vector<Mesh> meshes, Ref<Material> material);

		Ref<Material> GetMaterial();

		std::vector<Mesh> Meshes();

	protected:
		std::vector<Mesh> _meshes{};
		std::shared_ptr<Material> _material;

	};

}