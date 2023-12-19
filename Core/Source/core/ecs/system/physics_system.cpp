#include <stdafx.h>
#include "physics_system.h"
#include "core/ecs/component/physics_component.h"
#include "core/ecs/component/transform_component.h"

namespace Core::System {

	void Physics::Init()
	{
	}

	void Physics::Tick(Ref<entt::registry> registry, double dt)
	{
		auto view = registry->view<Component::Physics, Component::Transform>();
		for (auto entity : view) {

			auto& cPhysics = registry->get<Component::Physics>(entity);
			auto& cTransform = registry->get<Component::Transform>(entity);

			registry->patch<Component::Physics>(entity, [dt](Component::Physics& cPhysics) {
				cPhysics.acceleration.y -= 9.807;
				cPhysics.velocity += cPhysics.acceleration * glm::vec3(dt);
				cPhysics.acceleration = glm::vec3(0);
			});

			registry->patch<Component::Transform>(entity, [dt, cPhysics](Component::Transform& cTransform) {
				cTransform.position += cPhysics.velocity * glm::vec3(dt);
			});

		}
	}

	void Physics::PreRender(Ref<entt::registry> registry, double dt)
	{
	}

	void Physics::RenderPass(Ref<entt::registry> registry, double dt, uint32_t renderPass)
	{
	}

	void Physics::Gui(Ref<entt::registry> registry, double dt)
	{
	}

	void Physics::PostRender(Ref<entt::registry> registry, double dt)
	{
	}
}