#pragma once

#include "dll.h"
#include "core/ecs/system/system.h"

namespace Core {

	class ENGINE_API Scene {

	public:
		Scene();
		void Tick(double delta);
		void PreRender();
		void Render(uint32_t passIndex);
		void PostRender();
		Ref<entt::registry> GetRegistry();
		entt::entity CreateEntity(const char* name, entt::entity parent = entt::null);

		void SetParent(entt::entity entity, entt::entity parent);

	private:
		std::vector<Ref<System::System>>	_systems;
		Ref<entt::registry>					_registry;

	};

}