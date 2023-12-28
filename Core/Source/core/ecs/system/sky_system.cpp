#include "stdafx.h"
#include "sky_system.h"
#include "core/engine/engine.h"
#include "core/ecs/component/sky_component.h"
#include "core/asset/asset_shader.h"
#include "core/asset/asset_mesh.h"

namespace Core::System {

	void Sky::Init()
	{		
		_shader = ASSETS()->CopyAsset<AssetShader>("shader_sky");
		_mesh = Mesh((Primitive&)Point::Make({ 0, 0, 0 }));
	}

	void Sky::Tick(Ref<entt::registry> registry, double dt)
	{
	}

	void Sky::PreRender(Ref<entt::registry> registry)
	{
	}

	void Sky::RenderPass(Ref<entt::registry> registry, uint32_t passIndex)
	{

		auto view = registry->view<Component::Sky>();

		for (auto& entity : view) {
			_shader.Use();
			//GFX()->DepthRange(1.0, 1.0);
			GFX()->RenderMesh(_mesh, RENDER_STYLE_POINTS);
			//GFX()->DepthRange(0.0, 1.0);
		}

	}

	void Sky::Gui(Ref<entt::registry> registry, double dt)
	{
	}

	void Sky::PostRender(Ref<entt::registry> registry)
	{
	}


}