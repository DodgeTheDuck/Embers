#include <stdafx.h>
#include "scene.h"
#include "core/ecs/component/base_component.h"
#include <core/ecs/system/model_system.h>
#include <core/ecs/system/camera_system.h>
#include <core/ecs/system/physics_system.h>
#include <core/ecs/system/particle_emitter_system.h>

namespace Core {

	Scene::Scene() {
		_registry = CreateRef<entt::registry>();
		_systems.push_back(std::make_shared<System::Model>());
		_systems.push_back(std::make_shared<System::Camera>());
		_systems.push_back(std::make_shared<System::Physics>());
		_systems.push_back(std::make_shared<System::ParticleEmitter>());
		for (auto& system : _systems) {
			system->Init();
		}
	}

	void Scene::Tick(double delta)
	{
		for (auto& system : _systems) {
			system->Tick(_registry, delta);
		}
	}

	void Scene::PreRender()
	{
		for (auto& system : _systems) {
			system->PreRender(_registry);
		}
	}

	void Scene::Render(uint32_t passIndex)
	{
		for (auto& system : _systems) {
			system->RenderPass(_registry, passIndex);
		}
	}

	void Scene::PostRender()
	{
		for (auto& system : _systems) {
			system->PostRender(_registry);
		}
	}

	Ref<entt::registry> Scene::GetRegistry()
	{
		return _registry;
	}

	entt::entity Scene::CreateEntity(const char* name, entt::entity parent)
	{
		auto entity = _registry->create();
		auto base = Component::Base();
		base.name = name;		
		_registry->emplace<Component::Base>(entity, base);

		if (parent != entt::null) SetParent(entity, parent);

		return entity;
	}

	void Scene::SetParent(entt::entity entity, entt::entity parent)
	{		

		_registry->patch<Component::Base>(entity, [parent](Component::Base& base) {
			base.parent = parent;
		});
		_registry->patch<Component::Base>(parent, [this, entity](Component::Base& base) {
			if (base.first == entt::null) {
				base.first = entity;
			}
			else {
				auto nearestSibling = base.first;
				auto& nearestSiblingBase = _registry->get<Component::Base>(base.first);
				while (true) {
					if (nearestSiblingBase.next == entt::null) {
						_registry->patch<Component::Base>(base.first, [entity](Component::Base& childBase) {
							childBase.next = entity;
						});
						_registry->patch<Component::Base>(entity, [entity, nearestSibling](Component::Base& childBase) {
							childBase.prev = nearestSibling;
						});
						break;
					}
					nearestSibling = nearestSiblingBase.next;
					nearestSiblingBase = _registry->get<Component::Base>(nearestSibling);
				}
			}
		});
	}


}

