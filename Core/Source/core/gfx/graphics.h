#pragma once

#include <dll.h>
#include <core/gfx/graphics_pipeline.h>
#include <core/geometry/mesh.h>

namespace Core {

	class ENGINE_API Graphics {

	public:
		void Init(HINSTANCE hInstance, HWND hwnd);
		void SetPipeline(Ref<GraphicsPipeline> pipeline);
		Ref<GraphicsPipeline> GetPipeline();

		void BeginFrame();
		void RenderMesh(Mesh mesh);
		void EndFrame();

	private:
		void _InitDisplay(HINSTANCE hInstance, HWND hwnd);
		void _InitGraphics();
		HWND _CreateFakeWindow(HINSTANCE hInstance);

		// display
		HDC _dc{};

		// gfx
		Ref<GraphicsPipeline> _pipeline;


	};

}