#pragma once

namespace Core {

	class GraphicsState {
	public:
		virtual void Init() = 0;
		virtual void BeginFrame() = 0;
		virtual void EndFrame() = 0;

	};

}