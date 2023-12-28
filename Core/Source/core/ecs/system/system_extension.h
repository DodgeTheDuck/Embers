#pragma once

#include "system.h"

namespace Core::System {

	class ENGINE_API Extension : public System {		
	public:
		void Init() override = 0;
		void Tick(Ref<entt::registry> registry, double dt) override = 0;
		void PreRender(Ref<entt::registry> registry) override = 0;
		void RenderPass(Ref<entt::registry> registry, uint32_t passIndex) override = 0;
		void Gui(Ref<entt::registry> registry, double dt) override = 0;
		void PostRender(Ref<entt::registry> registry) override = 0;
	};

}