#include "stdafx.h"
#include "state_flare.h"
#include "gui/scene_explorer.h"
#include "gui/entity_viewer.h"
#include <core/asset/asset_model.h>
#include <core/asset/asset_mesh.h>
#include <core/asset/asset_shader.h>
#include <core/ecs/component/model_component.h>
#include <core/ecs/component/camera_component.h>
#include <core/ecs/component/sky_component.h>
#include <core/ecs/component/terrain_component.h>
#include <core/ecs/component/transform_component.h>
#include <core/gfx/graphics_pipeline_forward_basic.h>

namespace Flare {

	void StateFlare::Init()
	{

		auto scene = ENGINE().PushScene();
		ImGui::SetCurrentContext(GuiManager()->GetContext());
		Gfx()->SetPipeline(CreateRef<GraphicsPipelineForwardBasic>());
		auto sceneExplorer = CreateRef<Gui::SceneExplorer>(scene);
		auto entityViewer = CreateRef<Gui::EntityViewer>(sceneExplorer);

		GuiManager()->AddWidget(sceneExplorer);
		GuiManager()->AddWidget(entityViewer);

		auto terrain = ACTIVE_SCENE()->CreateEntity("terrain");
		auto sky = ACTIVE_SCENE()->CreateEntity("sky");
		auto camera = ACTIVE_SCENE()->CreateEntity("camera");

		auto& cTerrain = ACTIVE_SCENE()->GetRegistry()->emplace<Component::Terrain>(terrain);
		auto& cTransform = ACTIVE_SCENE()->GetRegistry()->emplace<Component::Transform>(terrain);

		cTerrain.nColumns = 128;
		cTerrain.scale = 1.0;

		auto& cCamera = ACTIVE_SCENE()->GetRegistry()->emplace<Component::Camera>(camera);
		auto& cCameraTrans = ACTIVE_SCENE()->GetRegistry()->emplace<Component::Transform>(camera);

		cCameraTrans.position = glm::vec3(10, 10, 10);

		cCamera.fov = 45;
		cCamera.viewNear = 0.01f;
		cCamera.viewFar = 1000.0f;
		cCamera.projection = glm::perspective(cCamera.fov, 1920.0f / 1080.0f, cCamera.viewNear, cCamera.viewFar);
		cCamera.view = glm::mat4();

		//auto& cSky = ACTIVE_SCENE()->GetRegistry()->emplace<Component::Sky>(sky);

	}

	void StateFlare::Tick(double dt)
	{

	}

}