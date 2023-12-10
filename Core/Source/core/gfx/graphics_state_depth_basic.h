#pragma once

#include "graphics_state.h"

namespace Core {

	class GraphicsStateDepthBasic : public GraphicsState {

		void Init() override;
		void BeginFrame() override;
		void EndFrame() override;

	};

}