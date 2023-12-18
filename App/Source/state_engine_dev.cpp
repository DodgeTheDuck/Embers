#include "stdafx.h"
#include <state_engine_dev.h>
#include <Core/engine/engine.h>
#include <core/ecs/component/model_component.h>
#include <core/ecs/component/camera_component.h>
#include <core/ecs/component/transform_component.h>
#include <Core/gfx/graphics.h>
#include <Core/gfx/graphics_pipeline_forward_basic.h>
#include <core/asset/asset_mesh.h>
#include <core/asset/asset_shader.h>
#include <core/geometry/primitive.h>
#include <core/base.h>

void StateEngineDev::Init()
{
	Core::Gfx()->SetPipeline(std::make_shared<Core::GraphicsPipelineForwardBasic>());

	auto testModel = Entities()->create();
	auto camera = Entities()->create();

	auto& cTestModelModel = Core::Entities()->emplace<Core::Component::Model>(testModel);
	auto& cTestModelTransform = Core::Entities()->emplace<Core::Component::Transform>(testModel);
	cTestModelModel.Meshes.push_back(Core::Assets()->CopyAsset<Core::AssetMesh>("mesh_rect"));
	cTestModelModel.Material = Material(Core::Assets()->CopyAsset<Core::AssetShader>("shader_particle"));

	auto& cCameraCamera = Core::Entities()->emplace<Core::Component::Camera>(camera);
	auto& cCameraTransform = Core::Entities()->emplace<Core::Component::Transform>(camera);

	cCameraCamera.fov = 90;
	cCameraCamera.viewNear = 0.1f;
	cCameraCamera.viewFar = 1000.0f;
	cCameraCamera.projection = glm::perspective(cCameraCamera.fov, 1024.0f / 768.0f, cCameraCamera.viewNear, cCameraCamera.viewFar);
	cCameraCamera.view = glm::mat4();

}

void StateEngineDev::Tick()
{
}

void StateEngineDev::Render()
{
}
