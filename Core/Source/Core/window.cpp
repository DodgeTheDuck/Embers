
#include "stdafx.h"
#include "window.h"
#include "engine.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Core {

	void Window::Create(HINSTANCE hInstance, int width, int height, LPCWSTR title, LPCWSTR className) {

		WNDCLASS wc = { };

		wc.lpfnWndProc = _MessageRouter;
		wc.hInstance = hInstance;
		wc.lpszClassName = className;

		RegisterClass(&wc);

		_hwnd = CreateWindowEx(
			0,
			className,
			title,
			WS_EX_OVERLAPPEDWINDOW,

			CW_USEDEFAULT, CW_USEDEFAULT, width, height,

			NULL,
			NULL,
			hInstance,
			NULL
		);

		if (_hwnd == NULL) {
			DWORD err = GetLastError();
			exit(1);
		}

		_dc = GetDC(_hwnd);

	}

	void Window::HandleEvents() {
		MSG msg = { };
		while (PeekMessage(&msg, _hwnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	void Window::Show() {
		ShowWindow(_hwnd, SW_NORMAL);
	}

	HWND Window::GetHwnd() {
		return _hwnd;
	}

	HDC Window::GetDeviceContext() {
		return _dc;
	}

	bool Window::IsClosing() {
		return _isClosing;
	}


	LRESULT CALLBACK Window::_MessageRouter(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		Window* app;
		if (msg == WM_CREATE)
		{
			app = (Window*)(((LPCREATESTRUCT)lParam)->lpCreateParams);
			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)app);
		}
		else
		{
			app = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		}
		return app->_WndProc(hWnd, msg, wParam, lParam);
	}

	LRESULT CALLBACK Window::_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{

		if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
			return true;

		switch (msg)
		{
		case WM_KEYDOWN:
			//GEngine().Keyboard()->SetKeyDown(wParam);
			break;
		case WM_KEYUP:
			//GEngine().Keyboard()->SetKeyUp(wParam);
			break;
		case WM_CLOSE:
			DestroyWindow(hWnd);
			break;
		case WM_DESTROY:
			CloseWindow(hWnd);
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
			break;
		}
		return 0;
	}

}