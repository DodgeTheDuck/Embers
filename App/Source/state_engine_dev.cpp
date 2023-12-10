#include "stdafx.h"
#include "state_engine_dev.h"
#include "Core/engine/engine.h"
#include "Core/gfx/graphics.h"
#include "Core/gfx/graphics_pipeline_forward_basic.h"

void StateEngineDev::Init()
{
	Core::Gfx().SetPipeline(std::make_shared<Core::GraphicsPipelineForwardBasic>());
}

void StateEngineDev::Tick()
{
}

void StateEngineDev::Render()
{
}
