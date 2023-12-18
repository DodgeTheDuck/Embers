#pragma once

namespace Core::Input {
	class Keyboard {
	public:
		bool GetKeyState(unsigned int keyCode);
		void SetKeyUp(unsigned int keyCode);
		void SetKeyDown(unsigned int keyCode);
	private:
		bool _keyStates[256];
	};
}