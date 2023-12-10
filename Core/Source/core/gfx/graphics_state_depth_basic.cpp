
#include "stdafx.h"
#include "graphics_state_depth_basic.h"

namespace Core {

	void GraphicsStateDepthBasic::Init() 
	{
		glViewport(0, 0, 1024, 768);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glClearColor(0, 0, 0, 1);
	}

	void GraphicsStateDepthBasic::BeginFrame()
	{
	}

	void GraphicsStateDepthBasic::EndFrame()
	{
	}

}