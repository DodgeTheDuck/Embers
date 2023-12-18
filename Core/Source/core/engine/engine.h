#pragma once

#include <core/display/window.h>
#include <core/engine/app_state.h>
#include <dll.h>
#include <core/gfx/graphics.h>
#include <core/engine/conductor.h>
#include <core/gui/gui.h>
#include <core/ecs/system/system.h>
#include <core/asset/asset_manager.h>
#include <core/input/keyboard.h>

namespace Core {

	class ENGINE_API EmbersEngine {

	public:
		void Init(HINSTANCE hInstance, Ref<AppState> bootstrappingState);
		void Run();

		Ref<Graphics>						GetGraphics();
		Ref<Input::Keyboard>				GetKeyboard();
		Ref<AssetManager>					GetAssetManager();
		Ref<entt::registry>					GetRegistry();

		// TODO: I don't like this name or what it does. Make this better.
		void PushAndInitAppState(Ref<AppState> appState);

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
		Ref<Graphics> _graphics;

		// gui
		Ref<Gui> _gui;

		// states
		std::queue<Ref<AppState>> _appStates;

		// assets
		Ref<AssetManager> _assetManager;

		// ecs
		Ref<entt::registry> _registry;
		std::vector<Ref<System::System>> _systems;

		// input
		Ref<Input::Keyboard> _keyboard;

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

	inline Ref<Graphics> Gfx() {
		return Engine().GetGraphics();
	}

	inline Ref<entt::registry> Entities() {
		return Engine().GetRegistry();
	}

	inline Ref<AssetManager> Assets() {
		return Engine().GetAssetManager();
	}

	inline Ref<Input::Keyboard> Keyboard() {
		return Engine().GetKeyboard();
	}


}