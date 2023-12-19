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

void StateEngineDev::Init()
{
	Gfx()->SetPipeline(std::make_shared<GraphicsPipelineForwardBasic>());

	auto camera = Entities()->create();
	auto emitter = Entities()->create();		

	auto& cCameraCamera = Entities()->emplace<Component::Camera>(camera);
	auto& cCameraTransform = Entities()->emplace<Component::Transform>(camera);

	cCameraCamera.fov = 90;
	cCameraCamera.viewNear = 0.1f;
	cCameraCamera.viewFar = 1000.0f;
	cCameraCamera.projection = glm::perspective(cCameraCamera.fov, 1024.0f / 768.0f, cCameraCamera.viewNear, cCameraCamera.viewFar);
	cCameraCamera.view = glm::mat4();

	auto& cEmitterEmitter = Entities()->emplace<Component::ParticleEmitter>(emitter);
	auto& cEmitterTransform = Entities()->emplace<Component::Transform>(emitter);

	cEmitterEmitter.lifeTimeS = 1.5;
	cEmitterEmitter.emitPerSec = 1024;
	cEmitterEmitter.emitDirection = glm::vec3(0, 1, 0);
	cEmitterEmitter.emitDirectionVariance = 20;
	cEmitterEmitter.emitVelocityMin = 5;
	cEmitterEmitter.emitVelocityMax = 8;
	cEmitterEmitter.emitColorMin = glm::vec3(0, 0, 0.4);
	cEmitterEmitter.emitColorMax = glm::vec3(0.8, 0.8, 1.0);
	cEmitterEmitter.partColorEnd = glm::vec3(0.8, 0.8, 1.0);

}

void StateEngineDev::Tick()
{
}

void StateEngineDev::Render()
{

}
