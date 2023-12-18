#pragma once

#include "graphics_state.h"

namespace Core {

	class GraphicsStateDepthBasic : public GraphicsState {

		void Init() override;

		void BeginFrame() override;

		void BeginPass(uint32_t passIndex) override;
		void EndPass(uint32_t passIndex) override;

		void EndFrame() override;

	};

}