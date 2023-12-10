#pragma once

#include "graphics_state.h"

namespace Core {

	class GraphicsPipeline {

	public:
		virtual void Init() = 0;
		virtual void BeginFrame() = 0;
		virtual void EndFrame() = 0;

	protected:
		std::unique_ptr<GraphicsState> _state;

	};

}