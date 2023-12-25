#include "stdafx.h"
#include "scene_explorer.h"
#include <core/ecs/component/base_component.h>

namespace Flare::Gui {

	void SceneExplorer::Draw()
	{
		ImGui::Begin("Scene Explorer");

		auto registry = ACTIVE_SCENE()->GetRegistry();
		auto view = registry->view<Component::Base>();

		if (ImGui::TreeNode("Scene")) {
			for (auto& entity : view) {
				auto& cBase = registry->get<Component::Base>(entity);
				if (cBase.parent == entt::null) {
					_DrawNode(entity, cBase);
				}
			}
			ImGui::TreePop();
		}

		ImGui::End();
	}

	void Gui::SceneExplorer::_DrawNode(entt::entity entity, Component::Base& baseComponent)
	{
		if (entity == entt::null) return;
		if (ImGui::TreeNode(baseComponent.name.c_str())) {
			if (baseComponent.first != entt::null) {
				auto registry = ACTIVE_SCENE()->GetRegistry();
				_DrawNode(baseComponent.first, registry->get<Component::Base>(baseComponent.first));
			}
			ImGui::TreePop();
		}
		if (baseComponent.next != entt::null) {
			auto registry = ACTIVE_SCENE()->GetRegistry();
			_DrawNode(baseComponent.next, registry->get<Component::Base>(baseComponent.next));
		}
	}

}