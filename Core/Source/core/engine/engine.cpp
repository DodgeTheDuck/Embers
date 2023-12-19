#include <stdafx.h>
#include <core/engine/engine.h>
#include <core/geometry/primitive.h>
#include <core/geometry/mesh.h>
#include <core/asset/asset_shader.h>
#include <core/asset/asset_mesh.h>
#include <core/ecs/system/model_system.h>
#include <core/ecs/system/camera_system.h>
#include <core/ecs/system/physics_system.h>
#include <core/ecs/system/particle_emitter_system.h>

namespace Core {
	
	void EmbersEngine::Init(HINSTANCE hInstance, Ref<AppState> bootstrappingState) {

		// setup window
		_window = Window();
		_window.Create(hInstance, 1024, 768, L"Ember Engine", L"emb_eng_win");
		_window.Show();

		// setup gfx
		_graphics = CreateRef<Graphics>();
		_graphics->Init(hInstance, _window.GetHwnd());

		// setup gui
		_gui = CreateRef<Gui>();
		_gui->Init(_window.GetHwnd());

		// setup input
		_keyboard = CreateRef<Input::Keyboard>();

		// setup assets
		_assetManager = CreateRef<AssetManager>();
		
		_assetManager->AddAsset<AssetShader>("shader_particle", std::make_shared<AssetShader>("particle.vert", "particle.frag"));
		_assetManager->AddAsset<AssetShader>("shader_particle_instanced", std::make_shared<AssetShader>("particle_instanced.vert", "particle_instanced.frag"));
		_assetManager->AddAsset<AssetMesh>("mesh_rect", CreateRef<AssetMesh>(
			(Primitive&)Rectangle::Make(1.0f, 1.0f, glm::vec3(1.0f))
		));

		// ecs
		_registry = CreateRef<entt::registry>();
		_systems.push_back(std::make_shared<System::Model>());
		_systems.push_back(std::make_shared<System::Camera>());
		_systems.push_back(std::make_shared<System::Physics>());
		_systems.push_back(std::make_shared<System::ParticleEmitter>());

		for (auto& system : _systems) {
			system->Init();
		}

		// add and initiate the client state
		PushAndInitAppState(bootstrappingState);

		// init conductor last to start timing as close to main loop as possible
		_conductor.Init();
		_tps = _conductor.CreateTimer("TPS", 1000.0 / 64.0);
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

	Ref<Graphics> EmbersEngine::GetGraphics()
	{
		return _graphics;
	}

	Ref<Input::Keyboard> EmbersEngine::GetKeyboard()
	{
		return _keyboard;
	}

	Ref<AssetManager> EmbersEngine::GetAssetManager()
	{
		return _assetManager;
	}
	
	Ref<entt::registry> EmbersEngine::GetRegistry() {
		return _registry;
	}

	void EmbersEngine::PushAndInitAppState(std::shared_ptr<AppState> appState) {
		_appStates.push(appState);
		appState->Init();
	}

	void EmbersEngine::_Tick(double dt)
	{
		_appStates.top()->Tick();

		for (auto& system : _systems) {
			system->Tick(_registry, dt);
		}

	}

	void EmbersEngine::_Render(double dt)
	{

		_graphics->BeginFrame();

		for (auto& system : _systems) {
			system->PreRender(_registry, dt);
		}

		_appStates.top()->Render();

		auto gfxPipeline = _graphics->GetPipeline();

		while (gfxPipeline->Process()) {
			
			auto passIndex = gfxPipeline->ActivePass();

			gfxPipeline->BeginPass();
						
			for (auto& system : _systems) {
				system->RenderPass(_registry, dt, passIndex);
			}
			
			gfxPipeline->EndPass();			
			gfxPipeline->NextPass();

		}

		_gui->Begin();
		_conductor.Gui();
		for (auto& system : _systems) {
			system->Gui(_registry, dt);
		}
		_gui->End();

		for (auto& system : _systems) {
			system->PostRender(_registry, dt);
		}

		_graphics->EndFrame();

	}

	EmbersEngine::~EmbersEngine() {

	}

}