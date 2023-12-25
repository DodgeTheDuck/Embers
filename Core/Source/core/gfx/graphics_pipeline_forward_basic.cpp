#include "stdafx.h"
#include "graphics_pipeline_forward_basic.h"
#include "graphics_state_depth_basic.h"
#include "core/engine/engine.h"
#include "core/asset/asset_shader.h"

namespace Core {

	GraphicsPipelineForwardBasic::GraphicsPipelineForwardBasic() {

	}

	void GraphicsPipelineForwardBasic::Init()
	{
		_state = CreateRef<GraphicsStateDepthBasic>();
		_state->Init();

		_stages.push_back(Core::GraphicsPipelinePass());
		_defaultShader = ASSETS()->CopyAsset<AssetShader>("shader_model");

	}

	void GraphicsPipelineForwardBasic::BeginFrame()
	{
		_state->BeginFrame();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void GraphicsPipelineForwardBasic::EndFrame()
	{
		_state->EndFrame();
	}	

	GraphicsPipelineForwardBasic::~GraphicsPipelineForwardBasic() {

	}

}