#pragma once

#include "core/ecs/system/system_extension.h"

namespace Core::System {

	class TerrainExtension : public Core::System::Extension {		
		void Init() override;
		void Tick(Ref<entt::registry> registry, double dt) override;
		void PreRender(Ref<entt::registry> registry) override;
		void RenderPass(Ref<entt::registry> registry, uint32_t passIndex) override;
		void Gui(Ref<entt::registry> registry, double dt) override;
		void PostRender(Ref<entt::registry> registry) override;
	};

}
