#include <stdafx.h>
#include <core/gfx/graphics_pipeline.h>

namespace Core {

	bool GraphicsPipeline::Process()
	{
		if (_activePass >= _stages.size()) {
			_activePass = 0;
			return false;
		}
		return true;
	}

	void GraphicsPipeline::BeginPass()
	{
		auto pass = _stages[_activePass];
		_state->BeginPass(_activePass);
		pass.Begin();
	}

	uint32_t GraphicsPipeline::ActivePass()
	{
		return _activePass;
	}

	void GraphicsPipeline::EndPass()
	{
		auto pass = _stages[_activePass];
		_state->EndPass(_activePass);
		pass.End();
	}

	void GraphicsPipeline::NextPass()
	{
		_activePass++;
	}	

	Ref<GraphicsState> GraphicsPipeline::State()
	{
		return _state;
	}

}