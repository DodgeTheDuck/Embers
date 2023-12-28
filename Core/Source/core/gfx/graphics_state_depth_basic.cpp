
#include "stdafx.h"
#include "graphics_state_depth_basic.h"

namespace Core {

	void GraphicsStateDepthBasic::Init() 
	{
		glViewport(0, 0, 1920, 1080);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glClearColor(0, 0, 0, 1);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void GraphicsStateDepthBasic::BeginFrame()
	{
	}

	void GraphicsStateDepthBasic::EndFrame()
	{
	}

	void GraphicsStateDepthBasic::BeginPass(uint32_t passIndex)
	{

	}

	void GraphicsStateDepthBasic::EndPass(uint32_t passIndex)
	{

	}

}