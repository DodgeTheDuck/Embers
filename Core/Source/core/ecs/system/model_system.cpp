#include <stdafx.h>
#include <core/ecs/component/model_component.h>
#include <core/ecs/component/transform_component.h>
#include <core/ecs/system/model_system.h>
#include <core/gfx/model.h>
#include <core/gfx/graphics.h>
#include <core/gfx/graphics_state.h>
#include <core/engine/engine.h>

namespace Core::System {

	void Model::Init()
	{
	}

	void Model::Tick(Ref<entt::registry> registry, double dt)
	{
	}

	void Model::PreRender(Ref<entt::registry> registry)
	{
	}

	void Model::RenderPass(Ref<entt::registry> registry, uint32_t passIndex)
	{

		auto view = registry->view<Component::Transform, Component::Model>();

		for (auto& entity : view) {
			auto& cModel = view.get<Component::Model>(entity);
			auto& cTransform = view.get<Component::Transform>(entity);			

			for (auto& mesh : cModel.Meshes) {
				cModel.Material.Apply(cTransform.Matrix(), mesh.Properties());
				Gfx()->RenderMesh(mesh);
			}
		}

	}

	void Model::Gui(Ref<entt::registry> registry, double dt)
	{
	}

	void Model::PostRender(Ref<entt::registry> registry)
	{
	}


}