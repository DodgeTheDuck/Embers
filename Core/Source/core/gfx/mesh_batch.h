#pragma once

#include "material.h"
#include "core/gl/vbo.h"
#include "core/geometry/mesh.h"

#define MAX_BATCH_INSTANCES 5000

namespace Core {

	class MeshBatch {

	public:
		MeshBatch();
		MeshBatch(Mesh mesh, Material material);

		void AddTransform(glm::mat4 transform);

		Mesh GetMesh();
		size_t InstanceCount();

		void Begin();
		void End();

	private:
		Mesh _mesh;
		Material _material;

		std::array<glm::mat4, MAX_BATCH_INSTANCES> _transforms;
		uint32_t _nextFreeIndex{};
		uint32_t _instanceCount{};

		Vbo _transformVbo;

	};

}