#include "stdafx.h"
#include "graphics_pipeline_forward_basic.h"
#include "graphics_state_depth_basic.h"

namespace Core {

	GraphicsPipelineForwardBasic::GraphicsPipelineForwardBasic() {

	}

	void GraphicsPipelineForwardBasic::Init()
	{
		_state = std::make_unique<GraphicsStateDepthBasic>();
		_state->Init();
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