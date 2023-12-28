#include "stdafx.h"
#include "scene_explorer.h"
#include <core/ecs/component/base_component.h>

namespace Flare::Gui {

	SceneExplorer::SceneExplorer(Ref<Scene> scene) {
		_scene = scene;
		_selectedEntity = entt::null;
	}

	void SceneExplorer::Draw()
	{

		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize(ImVec2(256, 1042));
		
		ImGui::Begin("Scene Explorer", nullptr, 
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoFocusOnAppearing |
			ImGuiWindowFlags_AlwaysVerticalScrollbar
		);

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

	entt::entity SceneExplorer::GetSelectedEntity() {
		return _selectedEntity;
	}

	Ref<entt::registry> SceneExplorer::GetRegistry() {
		return _scene->GetRegistry();
	}

	void SceneExplorer::_DrawNode(entt::entity entity, Component::Base& baseComponent)
	{
		if (entity == entt::null) return;
		if (ImGui::TreeNode(baseComponent.name.c_str())) {
			if (ImGui::IsItemClicked()) {
				_selectedEntity = entity;
			}
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