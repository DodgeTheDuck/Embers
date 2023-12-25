#pragma once

#include <core/gui/widget.h>
#include <core/ecs/component/base_component.h>

namespace Flare::Gui {

	class SceneExplorer : public Core::Gui::Widget {

	public:
		void Draw() override;

	private:
		void _DrawNode(entt::entity entity, Component::Base& baseComponent);

	};

}
