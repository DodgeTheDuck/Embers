#include "stdafx.h"
#include "entity_viewer.h"
#include "core/ecs/component/camera_component.h"

namespace Flare::Gui {
	
	EntityViewer::EntityViewer(Ref<SceneExplorer> explorer)
	{
		_explorer = explorer;
	}

	void EntityViewer::Draw()
	{

		auto entity = _explorer->GetSelectedEntity();
		auto registry = _explorer->GetRegistry();

		if (entity != entt::null) {
			auto& cBase = registry->get<Component::Base>(entity);
			ImGui::Begin(cBase.name.c_str());
			ImGui::End();
		}

	}

}