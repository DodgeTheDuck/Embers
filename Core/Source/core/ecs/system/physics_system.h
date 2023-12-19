#pragma once

#include "system.h"

namespace Core::System {

	class Physics : public System
	{
		void Init() override;
		void Tick(Ref<entt::registry> registry, double dt) override;
		void PreRender(Ref<entt::registry> registry, double dt) override;
		void RenderPass(Ref<entt::registry> registry, double dt, uint32_t renderPass) override;
		void Gui(Ref<entt::registry> registry, double dt) override;
		void PostRender(Ref<entt::registry> registry, double dt) override;
	};

}