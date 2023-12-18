#pragma once

#include "graphics_state.h"
#include "graphics_pipeline_stage.h"

namespace Core {

	class GraphicsPipeline {

	public:
		virtual void Init() = 0;
		virtual void BeginFrame() = 0;		

		bool Process();
		void BeginPass();
		uint32_t ActivePass();
		void EndPass();
		void NextPass();

		virtual void EndFrame() = 0;

		Ref<GraphicsState> State();

	protected:
		Ref<GraphicsState> _state;
		std::vector<GraphicsPipelinePass> _stages;
		uint32_t _activePass;

	};

}