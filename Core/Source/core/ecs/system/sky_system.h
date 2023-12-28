#pragma once

#include "system.h"
#include "core/gfx/shader_program.h"
#include "core/geometry/mesh.h"

namespace Core::System {

	class Sky : public System {
	public:
		void Init() override;
		void Tick(Ref<entt::registry> registry, double dt) override;
		void PreRender(Ref<entt::registry> registry) override;
		void RenderPass(Ref<entt::registry> registry, uint32_t passIndex) override;
		void Gui(Ref<entt::registry> registry, double dt) override;
		void PostRender(Ref<entt::registry> registry) override;
	private:
		Mesh _mesh;
		ShaderProgram _shader;
	};

}