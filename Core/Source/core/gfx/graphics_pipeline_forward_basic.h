#pragma once

#include "dll.h"
#include "graphics_pipeline.h"

namespace Core {

	class ENGINE_API GraphicsPipelineForwardBasic : public GraphicsPipeline {

	public:
		GraphicsPipelineForwardBasic();
		~GraphicsPipelineForwardBasic();

		void Init() override;

		void BeginFrame() override;
		void EndFrame() override;

	};

}