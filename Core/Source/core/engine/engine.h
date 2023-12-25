#pragma once

#include <core/display/window.h>
#include <core/engine/app_state.h>
#include <dll.h>
#include <core/gfx/graphics.h>
#include <core/engine/conductor.h>
#include <core/engine/scene.h>
#include <core/gui/gui.h>
#include <core/ecs/system/system.h>
#include <core/asset/asset_manager.h>
#include <core/input/keyboard.h>

#define ENGINE() EmbersEngine::GetInstance()
#define GFX() EmbersEngine::GetInstance().GetGraphics()
#define ACTIVE_SCENE() EmbersEngine::GetInstance().GetActiveScene()
#define ASSETS() EmbersEngine::GetInstance().GetAssetManager()

namespace Core {

	class ENGINE_API EmbersEngine {

	public:
		void Init(HINSTANCE hInstance, Ref<AppState> bootstrappingState);
		void Run();
		
		Ref<Graphics>						GetGraphics() const;
		Ref<Input::Keyboard>				GetKeyboard() const;
		Ref<AssetManager>					GetAssetManager() const;
		Ref<Gui::GuiManager>				GetGuiManager() const;
		Ref<Scene>							GetActiveScene() const;

		void PushAppState(Ref<AppState> appState);
		void PushScene();

		static EmbersEngine& GetInstance() {
			static EmbersEngine instance;
			return instance;
		}

	private:

		void _Tick(double dt);
		void _Render(double dt);
		~EmbersEngine();
		
		Window								_window;
		Ref<Graphics>						_graphics;
		Ref<Gui::GuiManager>				_gui;
		Ref<AssetManager>					_assetManager;
		Ref<Input::Keyboard>				_keyboard;
		std::queue<Ref<Scene>>				_scenes;
		std::stack<Ref<AppState>>			_appStates;		
		
		Conductor			_conductor;
		conductor_timer		_tps{};
		conductor_timer		_fps{};		

	};

	inline EmbersEngine& Engine() {
		return EmbersEngine::GetInstance();
	}

	inline Ref<Graphics> Gfx() {
		return Engine().GetGraphics();
	}

	inline Ref<Gui::GuiManager> GuiManager() {
		return Engine().GetGuiManager();
	}

	inline Ref<AssetManager> Assets() {
		return Engine().GetAssetManager();
	}

	inline Ref<Input::Keyboard> Keyboard() {
		return Engine().GetKeyboard();
	}

}