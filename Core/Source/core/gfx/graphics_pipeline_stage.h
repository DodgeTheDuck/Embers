#pragma once

#include "core/gl/fbo.h"

namespace Core {

	class GraphicsPipelinePass {

	public:
		void Begin();
		void End();

	private:
		Fbo _fbo;

	};

}