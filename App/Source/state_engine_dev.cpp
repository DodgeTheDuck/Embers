#include "stdafx.h"
#include <state_engine_dev.h>
#include <Core/engine/engine.h>
#include <core/ecs/component/model_component.h>
#include <core/ecs/component/camera_component.h>
#include <core/ecs/component/transform_component.h>
#include <core/ecs/component/particle_emitter_component.h>
#include <Core/gfx/graphics.h>
#include <Core/gfx/graphics_pipeline_forward_basic.h>
#include <core/asset/asset_mesh.h>
#include <core/asset/asset_shader.h>
#include <core/geometry/primitive.h>
#include <core/base.h>
#include <core/asset/asset_texture.h>

void StateEngineDev::Init()
{
	Gfx()->SetPipeline(std::make_shared<GraphicsPipelineForwardBasic>());

	auto camera = Entities()->create();
	auto model = Entities()->create();

	auto& cModelModel = Entities()->emplace<Component::Model>(model);
	auto& cModelTransform = Entities()->emplace<Component::Transform>(model);

	auto mesh = Assets()->CopyAsset<AssetMesh>("mesh_rect");
	mesh.Properties().textures[MaterialTextureType::ALBEDO] = Assets()->CopyAsset<AssetTexture>("texture_unicorn");

	cModelModel.Meshes.push_back(mesh);
	cModelModel.Material = Material(Assets()->CopyAsset<AssetShader>("shader_model"));

	auto& cCameraCamera = Entities()->emplace<Component::Camera>(camera);
	auto& cCameraTransform = Entities()->emplace<Component::Transform>(camera);

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
