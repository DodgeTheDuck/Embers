#include "stdafx.h"
#include "state_flare.h"
#include "gui/scene_explorer.h"
#include <core/asset/asset_model.h>
#include <core/ecs/component/model_component.h>
#include <core/ecs/component/camera_component.h>
#include <core/ecs/component/transform_component.h>
#include <core/gfx/graphics_pipeline_forward_basic.h>

namespace Flare {

	void StateFlare::Init()
	{

		ENGINE().PushScene();
		ImGui::SetCurrentContext(GuiManager()->GetContext());
		Gfx()->SetPipeline(CreateRef<GraphicsPipelineForwardBasic>());
		GuiManager()->AddWidget(CreateRef<Gui::SceneExplorer>());

		auto armour = ACTIVE_SCENE()->CreateEntity("armour");
		auto camera = ACTIVE_SCENE()->CreateEntity("camera");

		auto& cModel = ACTIVE_SCENE()->GetRegistry()->emplace<Component::Model>(armour);
		auto& cTransform = ACTIVE_SCENE()->GetRegistry()->emplace<Component::Transform>(armour);
		cTransform.scale = glm::vec3(0.1);
		auto armorModel = ASSETS()->CopyAsset<AssetModel>("model_armour");
		cModel.Material = armorModel.GetMaterial();
		cModel.Meshes = armorModel.GetMeshes();

		auto& cCamera = ACTIVE_SCENE()->GetRegistry()->emplace<Component::Camera>(camera);
		auto& cCameraTrans = ACTIVE_SCENE()->GetRegistry()->emplace<Component::Transform>(camera);

		cCamera.fov = 90;
		cCamera.viewNear = 0.1f;
		cCamera.viewFar = 1000.0f;
		cCamera.projection = glm::perspective(cCamera.fov, 1024.0f / 768.0f, cCamera.viewNear, cCamera.viewFar);
		cCamera.view = glm::mat4();

	}

	void StateFlare::Tick(double dt)
	{

	}

}