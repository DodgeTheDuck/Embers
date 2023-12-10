
#include "stdafx.h"
#include "engine.h"

namespace Core {
	
	void EmbersEngine::Init(HINSTANCE hInstance, std::shared_ptr<AppState> bootstrappingState) {

		// setup window
		_window = Window();
		_window.Create(hInstance, 1024, 768, L"Ember Engine", L"emb_eng_win");
		_window.Show();

		// setup gfx
		_graphics.InitDisplay(hInstance, _window.GetHwnd());
		_graphics.InitGraphics();

		// setup gui
		_gui.Init(_window.GetHwnd());

		// add and initiate the client state
		PushAppState(bootstrappingState);
		bootstrappingState->Init();

		// init conductor last to start timing as close to main loop as possible
		_conductor.Init();
		_tps = _conductor.CreateTimer("TPS", 1000.0 / 128.0);
		_fps = _conductor.CreateTimer("FPS", 1000.0 / 1024.0);

	}

	void EmbersEngine::Run() {
		while (!_window.IsClosing()) {
			_conductor.Tick();
			double delta{};
			if (_conductor.Query(_tps, delta)) _Tick(delta);
			if (_conductor.Query(_fps, delta)) _Render(delta);		
			_window.HandleEvents();
		}
	}

	void EmbersEngine::PushAppState(std::shared_ptr<AppState> appState) {
		_appStates.push(appState);
	}

	void EmbersEngine::_Tick(double dt)
	{
		_appStates.front()->Tick();
	}

	void EmbersEngine::_Render(double dt)
	{

		_appStates.front()->Render();

		_graphics.Clear();

		_gui.Begin();
		_conductor.Gui();
		_gui.End();

		_graphics.Swap();

	}

	EmbersEngine::~EmbersEngine() {

	}

}