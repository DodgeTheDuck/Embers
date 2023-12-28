#pragma once

#include "dll.h"
#include "graphics_state.h"
#include "graphics_pipeline_stage.h"
#include "shader_program.h"

namespace Core {

	class ENGINE_API GraphicsPipeline {

	public:
		virtual void Init() = 0;
		virtual void BeginFrame() = 0;		

		bool Process();
		void BeginPass();
		uint32_t ActivePassIndex();
		void EndPass();
		void NextPass();

		ShaderProgram DefaultShader();

		virtual void EndFrame() = 0;

		GraphicsState& State();

	protected:
		Ref<GraphicsState> _state;
		std::vector<GraphicsPipelinePass> _stages;
		uint32_t _activePass;
		ShaderProgram _defaultShader;

	};

}