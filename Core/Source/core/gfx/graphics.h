#pragma once

#include "dll.h"
#include "graphics_pipeline.h"

namespace Core {

	class ENGINE_API Graphics {

	public:
		void Init(HINSTANCE hInstance, HWND hwnd);
		void SetPipeline(std::shared_ptr<GraphicsPipeline> pipeline);

		void BeginFrame();
		void EndFrame();

	private:
		void _InitDisplay(HINSTANCE hInstance, HWND hwnd);
		void _InitGraphics();
		HWND _CreateFakeWindow(HINSTANCE hInstance);

		// display
		HDC _dc;

		// gfx
		std::shared_ptr<GraphicsPipeline> _pipeline;


	};

}