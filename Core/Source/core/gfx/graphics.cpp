#include <stdafx.h>
#include <core/gfx/graphics.h>

namespace Core {

	void Graphics::Init(HINSTANCE hInstance, HWND hwnd)
	{
		_InitDisplay(hInstance, hwnd);
		_InitGraphics();
	}

	uint32_t Graphics::RegisterBatch(Mesh mesh, Material material) {
		_batches.push_back(CreateRef<MeshBatch>(mesh, material));
		return (uint32_t)_batches.size()-1;
	}

	void Graphics::PostToBatch(uint32_t handle, glm::mat4 transform)
	{
		_batches[handle]->AddTransform(transform);
	}

	void Graphics::SubmitBatch(uint32_t handle)
	{
		auto& batch = _batches[handle];
		batch->Begin();
		glDrawElementsInstanced(GL_TRIANGLES, batch->GetMesh().IndexCount(), GL_UNSIGNED_INT, (void*)0, batch->InstanceCount());
		batch->End();
	}

	uint32_t Graphics::QueryBatch(uint32_t handle)
	{
		return _batches[handle]->InstanceCount();
	}

	void Graphics::DepthRange(double viewNear, double viewFar)
	{
		glDepthRange(viewNear, viewFar);
	}

	void Graphics::BeginFrame() {
		if (_pipeline != nullptr) {
			_pipeline->BeginFrame();
		}
	}

	void Graphics::RenderMesh(Mesh& mesh, RenderStyle style)
	{
		mesh.Bind();		
		glDrawElements(style, mesh.IndexCount(), GL_UNSIGNED_INT, (void*)0);
	}

	void Graphics::EndFrame() {
		if (_pipeline != nullptr) {
			_pipeline->EndFrame();
		}
		SwapBuffers(_dc);
	}

	void Graphics::SetPipeline(Ref<GraphicsPipeline> pipeline)
	{
		_pipeline = pipeline;
		_pipeline->Init();
	}

	Ref<GraphicsPipeline> Graphics::GetPipeline()
	{
		return _pipeline;
	}

	void Graphics::_InitDisplay(HINSTANCE hInstance, HWND hwnd)
	{

		PIXELFORMATDESCRIPTOR pfdFake =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA,
			32,
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			24,
			8,
			0,
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};

		HWND fakeHwnd = _CreateFakeWindow(hInstance);

		if (fakeHwnd == NULL) {
			DWORD err = GetLastError();
			exit(-1);
		}

		HDC fakeDc = GetDC(fakeHwnd);

		int fakePixelFormat = ChoosePixelFormat(fakeDc, &pfdFake);
		SetPixelFormat(fakeDc, fakePixelFormat, &pfdFake);

		HGLRC fakeRc = wglCreateContext(fakeDc);
		wglMakeCurrent(fakeDc, fakeRc);

		if (!gladLoadGL() || !gladLoadWGL(fakeDc)) {
			exit(-1);
		}

		const int pixelAttribs[] = {
			WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
			WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
			WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
			WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
			WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
			WGL_COLOR_BITS_ARB, 32,
			WGL_ALPHA_BITS_ARB, 8,
			WGL_DEPTH_BITS_ARB, 24,
			WGL_STENCIL_BITS_ARB, 8,
			WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
			WGL_SAMPLES_ARB, 4,
			0
		};

		int pixelFormat;
		uint32_t numFormats;

		_dc = GetDC(hwnd);

		bool success = wglChoosePixelFormatARB(_dc, pixelAttribs, NULL, 1, &pixelFormat, &numFormats);

		if (!success || numFormats == 0) {
			exit(-1);
		}

		PIXELFORMATDESCRIPTOR pfd;
		DescribePixelFormat(_dc, pixelFormat, sizeof(pfd), &pfd);
		SetPixelFormat(_dc, pixelFormat, &pfd);

		const int major_min = 4, minor_min = 5;
		int  contextAttribs[] = {
			WGL_CONTEXT_MAJOR_VERSION_ARB, major_min,
			WGL_CONTEXT_MINOR_VERSION_ARB, minor_min,
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			0
		};

		HGLRC context = glad_wglCreateContextAttribsARB(_dc, 0, contextAttribs);

		if (context == NULL) {
			exit(-1);
		}

		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(fakeRc);
		ReleaseDC(fakeHwnd, fakeDc);
		DestroyWindow(fakeHwnd);

		wglMakeCurrent(_dc, context);

		if (!gladLoadGL() || !gladLoadWGL(fakeDc)) {
			exit(-1);
		}

	}

	void Graphics::_InitGraphics()
	{
		wglSwapIntervalEXT(0);
	}	

	HWND Graphics::_CreateFakeWindow(HINSTANCE hInstance) {

		WNDCLASSEX wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = DefWindowProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = L"emb_gl_init";
		wcex.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);

		RegisterClassEx(&wcex);

		return CreateWindow(L"emb_gl_init", L"", WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CS_OWNDC, 256, 256, 128, 128, NULL, NULL, hInstance, NULL);

	}

}