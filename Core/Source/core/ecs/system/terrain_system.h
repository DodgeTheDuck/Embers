#pragma once

#include "system.h"
#include "core/geometry/mesh.h"
#include "core/gfx/shader_program.h"
#include "core/gl/texture.h"

namespace Core::System {

	class Terrain : public System {
	public:
		void Init() override;
		void Tick(Ref<entt::registry> registry, double dt) override;
		void PreRender(Ref<entt::registry> registry) override;
		void RenderPass(Ref<entt::registry> registry, uint32_t passIndex) override;
		void Gui(Ref<entt::registry> registry, double dt) override;
		void PostRender(Ref<entt::registry> registry) override;
	private:
		Texture _heightMap;
		Texture _grass;
		Texture _stone;
		ShaderProgram _shader;
		Mesh _mesh;

		int _uni_v{-1};
		int _uni_p{-1};
		int _uni_chunk_x{-1};
		int _uni_chunk_y{-1};
		int _uni_max_chunks{-1};
		int _uni_scale{-1};
		int _uni_lod{-1};
		int _uni_view_pos{ -1 };

	};

}