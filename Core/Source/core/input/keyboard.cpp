#include <stdafx.h>
#include "keyboard.h"

namespace Core::Input {

	bool Keyboard::GetKeyState(unsigned int keyCode) {
		return _keyStates[keyCode];
	}

	void Keyboard::SetKeyUp(unsigned int keyCode) {
		_keyStates[keyCode] = false;
	}

	void Keyboard::SetKeyDown(unsigned int keyCode) {
		_keyStates[keyCode] = true;
	}

}