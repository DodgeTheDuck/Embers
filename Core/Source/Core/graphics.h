#pragma once

namespace Core {

	class Graphics {

	public:
		void InitDisplay(HINSTANCE hInstance, HWND hwnd);
		void InitGraphics();

		void Clear();
		void Swap();

	private:
		HWND _CreateFakeWindow(HINSTANCE hInstance);

		HDC _dc;

	};

}