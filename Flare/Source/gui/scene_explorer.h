#pragma once

#include <core/gui/widget.h>
#include <core/engine/scene.h>
#include <core/ecs/component/base_component.h>

namespace Flare::Gui {

	class SceneExplorer : public Core::Gui::Widget {

	public:
		SceneExplorer(Ref<Scene> scene);
		void Draw() override;
		entt::entity GetSelectedEntity();
		Ref<entt::registry> GetRegistry();

	private:
		void _DrawNode(entt::entity entity, Component::Base& baseComponent);
		Ref<Scene> _scene;
		entt::entity _selectedEntity;

	};

}
