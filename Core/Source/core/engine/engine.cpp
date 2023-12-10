
#include "stdafx.h"
#include "engine.h"

namespace Core {
	
	void EmbersEngine::Init(HINSTANCE hInstance, std::shared_ptr<AppState> bootstrappingState) {

		// setup window
		_window = Window();
		_window.Create(hInstance, 1024, 768, L"Ember Engine", L"emb_eng_win");
		_window.Show();

		// setup gfx
		_graphics.Init(hInstance, _window.GetHwnd());

		// setup gui
		_gui.Init(_window.GetHwnd());

		// add and initiate the client state
		PushAndInitAppState(bootstrappingState);
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

	Graphics& EmbersEngine::GetGraphics()
	{
		return _graphics;
	}

	void EmbersEngine::PushAndInitAppState(std::shared_ptr<AppState> appState) {
		_appStates.push(appState);
		appState->Init();
	}

	void EmbersEngine::_Tick(double dt)
	{
		_appStates.front()->Tick();
	}

	void EmbersEngine::_Render(double dt)
	{

		_graphics.BeginFrame();

		_appStates.front()->Render();

		_gui.Begin();
		_conductor.Gui();
		_gui.End();

		_graphics.EndFrame();

	}

	EmbersEngine::~EmbersEngine() {

	}

}