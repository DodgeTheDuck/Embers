#include "stdafx.h"
#include "graphics.h"

namespace Core {

	void Graphics::InitDisplay(HINSTANCE hInstance, HWND hwnd)
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

	void Graphics::InitGraphics()
	{
		//TODO: explode this out in to something more configurable
		wglSwapIntervalEXT(0);
		glViewport(0, 0, 1024, 768);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glClearColor(0, 0, 0, 1);
	}

	void Graphics::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Graphics::Swap() {
		SwapBuffers(_dc);
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