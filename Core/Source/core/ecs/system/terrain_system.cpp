#include "stdafx.h"
#include "terrain_system.h"
#include "core/geometry/primitive.h"
#include "core/engine/engine.h"
#include "core/asset/asset_shader.h"
#include "core/asset/asset_texture.h"
#include "core/ecs/component/terrain_component.h"

namespace Core::System {

	void Terrain::Init()
	{
		_mesh = Mesh((Primitive&)Point::Make({ 0, 0, 0 }));
		_shader = ASSETS()->CopyAsset<AssetShader>("shader_terrain");
		_heightMap = ASSETS()->CopyAsset<AssetTexture>("texture_height_map");
		_grass = ASSETS()->CopyAsset<AssetTexture>("texture_grass");
		_stone = ASSETS()->CopyAsset<AssetTexture>("texture_stone");
		_uni_p = _shader.GetUniformLocation("u_p");
		_uni_v = _shader.GetUniformLocation("u_v");
		_uni_scale = _shader.GetUniformLocation("u_scale");
		_uni_chunk_x = _shader.GetUniformLocation("u_chunk_x");
		_uni_chunk_y = _shader.GetUniformLocation("u_chunk_y");
		_uni_lod = _shader.GetUniformLocation("u_lod");
		_uni_max_chunks = _shader.GetUniformLocation("u_max_chunks");
		_uni_view_pos = _shader.GetUniformLocation("u_cam_pos");
	}

	void Terrain::Tick(Ref<entt::registry> registry, double dt)
	{
	}

	void Terrain::PreRender(Ref<entt::registry> registry)
	{
	}

	void Terrain::RenderPass(Ref<entt::registry> registry, uint32_t passIndex)
	{

		auto view = registry->view<Component::Terrain>();

		for (auto& entity : view) {
			auto& cTerrain = view.get<Component::Terrain>(entity);
			auto& state = Gfx()->GetPipeline()->State();

			auto camPos = state.GetCameraPosition();
			int camX = round(camPos.x);
			int camZ = round(camPos.z);
			int lodScale = 2;
			_shader.Use();
			_heightMap.Bind(0);
			_grass.Bind(1);
			_stone.Bind(2);
			_shader.UniformMat4(state.GetProjectionMatrix(), _uni_p);
			_shader.UniformMat4(state.GetViewMatrix(), _uni_v);
			_shader.UniformVec3(state.GetCameraPosition(), _uni_view_pos);
			_shader.UniformFloat(cTerrain.scale, _uni_scale);
			_shader.UniformUInt(cTerrain.nColumns, _uni_max_chunks);

			_mesh.Bind();			
			glDrawElementsInstanced(GL_POINTS, 1, GL_UNSIGNED_INT, (void*)0, cTerrain.nColumns * cTerrain.nColumns);			

		}

	}

	void Terrain::Gui(Ref<entt::registry> registry, double dt)
	{
	}

	void Terrain::PostRender(Ref<entt::registry> registry)
	{
	}


}