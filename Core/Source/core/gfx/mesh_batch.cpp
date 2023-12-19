#include <stdafx.h>
#include "mesh_batch.h"
#include "core/engine/engine.h"

namespace Core {

	MeshBatch::MeshBatch() {};

	MeshBatch::MeshBatch(Mesh mesh, Material material) {
		_mesh = mesh;
		_material = material;		
	}

	void MeshBatch::AddTransform(glm::mat4 transform) {
		_transforms[_nextFreeIndex] = transform;
		_nextFreeIndex++;
		_instanceCount++;
	}

	Mesh MeshBatch::GetMesh()
	{
		return _mesh;
	}

	size_t MeshBatch::InstanceCount()
	{
		return _transforms.size();
	}

	void MeshBatch::Begin() {
		
		if (_instanceCount == 0) return;

		if (_transformVbo.IsValid()) {
			Error::Exit(L"Tried to begin dirty batch");
		}

		_transformVbo.GenerateBuffer();
		_transformVbo.BufferData(_transforms.data(), _instanceCount, sizeof(glm::mat4));

		Vao meshVao = _mesh.GetVao();				
		meshVao.Bind();
		_transformVbo.Bind();

		std::size_t vec4Size = sizeof(glm::vec4);
		meshVao.VertexAttribPointer(3, 4, GL_FLOAT, 4 * vec4Size, (void*)0);
		meshVao.VertexAttribPointer(4, 4, GL_FLOAT, 4 * vec4Size, (void*)(1 * vec4Size));
		meshVao.VertexAttribPointer(5, 4, GL_FLOAT, 4 * vec4Size, (void*)(2 * vec4Size));
		meshVao.VertexAttribPointer(6, 4, GL_FLOAT, 4 * vec4Size, (void*)(3 * vec4Size));
		meshVao.VertexAttribDivisor(3, 1);
		meshVao.VertexAttribDivisor(4, 1);
		meshVao.VertexAttribDivisor(5, 1);
		meshVao.VertexAttribDivisor(6, 1);		

		_material.Apply(Gfx()->GetPipeline()->State(), glm::mat4());

	}

	void MeshBatch::End()
	{

		if (_instanceCount == 0) return;

		if (!_transformVbo.IsValid()) {
			Error::Exit(L"Tried to end an invalid batch");
		}
		_mesh.GetVao().Bind();
		_transformVbo.Unbind();
		_mesh.GetVao().Unbind();
		_transformVbo.Delete();
		_nextFreeIndex = 0;
		_instanceCount = 0;
	}	

}