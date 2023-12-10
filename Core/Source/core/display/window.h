#pragma once

namespace Core {

	class Window {
	public:
		Window() = default;
		~Window() = default;

		void Create(HINSTANCE hInstance, int width, int height, LPCWSTR title, LPCWSTR className);
		void Show();
		void HandleEvents();
		bool IsClosing();
		HWND GetHwnd();
		HDC GetDeviceContext();

	private:
		static LRESULT CALLBACK _MessageRouter(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		LRESULT CALLBACK _WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		HWND _hwnd;
		HDC _dc;
		bool _isClosing;
	};

}