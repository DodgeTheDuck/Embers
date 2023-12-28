#pragma once

#include <core/gui/widget.h>
#include <core/ecs/component/base_component.h>
#include "scene_explorer.h"

namespace Flare::Gui {

	class EntityViewer : public Core::Gui::Widget {

	public:
		EntityViewer(Ref<SceneExplorer> explorer);
		void Draw() override;

	private:
		Ref<SceneExplorer> _explorer;

	};

}
