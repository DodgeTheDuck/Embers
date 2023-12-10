
#include "stdafx.h"
#include "state_bootstrapper.h"
#include "Core/engine/engine.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
	Core::Engine().Init(hInstance, std::make_shared<StateBootsrapper>());
	Core::Engine().Run();
	return 0;
}