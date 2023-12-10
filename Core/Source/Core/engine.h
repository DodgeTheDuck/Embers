#pragma once

#include "window.h"
#include "app_state.h"
#include "dll.h"
#include "graphics.h"
#include "conductor.h"
#include "gui.h"

namespace Core {

	class ENGINE_API EmbersEngine {

	public:
		void Init(HINSTANCE hInstance, std::shared_ptr<AppState> bootstrappingState);
		void Run();

		void PushAppState(std::shared_ptr<AppState> appState);

		static EmbersEngine& GetInstance() {
			static EmbersEngine instance;
			return instance;
		}

	private:

		void _Tick(double dt);
		void _Render(double dt);
		~EmbersEngine();

		// display
		Window _window;

		// graphics
		Graphics _graphics;

		// gui
		Gui _gui;

		// states
		std::queue< std::shared_ptr<AppState>> _appStates;

		// timing
		Conductor _conductor;
		conductor_timer _tps;
		conductor_timer _fps;

		double _secAcc{};
		double _tpsAcc{};
		double _fpsAcc{};

	};

	inline EmbersEngine& Engine() {
		return EmbersEngine::GetInstance();
	}

}