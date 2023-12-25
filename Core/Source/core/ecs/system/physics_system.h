#pragma once

#include "system.h"

namespace Core::System {

	class Physics : public System
	{
		void Init() override;
		void Tick(Ref<entt::registry> registry, double dt) override;
		void PreRender(Ref<entt::registry> registry) override;
		void RenderPass(Ref<entt::registry> registry, uint32_t renderPass) override;
		void Gui(Ref<entt::registry> registry, double dt) override;
		void PostRender(Ref<entt::registry> registry) override;
	};

}