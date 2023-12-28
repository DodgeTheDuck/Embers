#include <stdafx.h>
#include <core/engine/engine.h>
#include <core/geometry/primitive.h>
#include <core/geometry/mesh.h>
#include <core/asset/asset_shader.h>
#include <core/loader/model_loader.h>
#include <core/asset/asset_model.h>
#include <core/asset/asset_texture.h>
#include <core/asset/asset_mesh.h>
#include <core/gl/texture.h>

namespace Core {
	
	void EmbersEngine::Init(HINSTANCE hInstance, Ref<AppState> bootstrappingState) {

		// setup window
		_window = Window();
		_window.Create(hInstance, 1920, 1080, L"Ember Engine", L"emb_eng_win");
		_window.Show();

		// setup gfx
		_graphics = CreateRef<Graphics>();
		_graphics->Init(hInstance, _window.GetHwnd());

		// setup gui
		_gui = CreateRef<Gui::GuiManager>();
		_gui->Init(_window.GetHwnd());

		// setup input
		_keyboard = CreateRef<Input::Keyboard>();

		// setup assets
		_assetManager = CreateRef<AssetManager>();

		_assetManager->AddAsset<AssetTexture>("texture_height_map", std::make_shared<AssetTexture>("height_map.png"));
		_assetManager->AddAsset<AssetTexture>("texture_grass", std::make_shared<AssetTexture>("grass.jpg"));
		_assetManager->AddAsset<AssetTexture>("texture_stone", std::make_shared<AssetTexture>("stone.jpg"));

		_assetManager->AddAsset<AssetShader>("shader_model", std::make_shared<AssetShader>("model.vert", "model.frag"));
		_assetManager->AddAsset<AssetShader>("shader_terrain", std::make_shared<AssetShader>("terrain.vert", "terrain.geom", "terrain.frag"));
		_assetManager->AddAsset<AssetShader>("shader_sky", std::make_shared<AssetShader>("sky.vert", "sky.geom", "sky.frag"));
		_assetManager->AddAsset<AssetShader>("shader_particle_instanced", std::make_shared<AssetShader>("particle_instanced.vert", "particle_instanced.frag"));

		_assetManager->AddAsset<AssetMesh>("mesh_rect", CreateRef<AssetMesh>(
			(Primitive&)Rectangle::Make(1.0f, 1.0f, glm::vec3(1.0f))
		));

		/*auto model = ModelLoader().Load("roman_armour/armour_hd.glb");
		_assetManager->AddAsset<AssetModel>("model_armour", std::make_shared<AssetModel>(model->GetMeshes(), model->GetMaterial()));*/

		// add and initiate the client state
		PushAppState(bootstrappingState);
		
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

	Ref<Graphics> EmbersEngine::GetGraphics() const
	{
		return _graphics;
	}

	Ref<Input::Keyboard> EmbersEngine::GetKeyboard() const
	{
		return _keyboard;
	}

	Ref<AssetManager> EmbersEngine::GetAssetManager() const
	{
		return _assetManager;
	}

	Ref<Gui::GuiManager> EmbersEngine::GetGuiManager() const
	{
		return _gui;
	}

	Ref<Scene> EmbersEngine::GetActiveScene() const
	{
		return _scenes.front();
	}

	void EmbersEngine::PushAppState(Ref<AppState> appState) {
		_appStates.push(appState);
		appState->Init();
	}

	Ref<Scene> EmbersEngine::PushScene() {
		auto scene = CreateRef<Scene>();
		_scenes.push(scene);
		return scene;
	}

	void EmbersEngine::_Tick(double dt)
	{
		_appStates.top()->Tick(dt);
		if (_scenes.size() > 0) _scenes.front()->Tick(dt);
	}

	void EmbersEngine::_Render(double dt)
	{

		// rendering
		_graphics->BeginFrame();

		if (_scenes.size() > 0) _scenes.front()->PreRender();

		auto gfxPipeline = _graphics->GetPipeline();

		if (gfxPipeline != nullptr) {
			while (gfxPipeline->Process()) {
				auto passIndex = gfxPipeline->ActivePassIndex();
				gfxPipeline->BeginPass();
				if(_scenes.size() > 0) _scenes.front()->Render(passIndex);
				gfxPipeline->EndPass();
				gfxPipeline->NextPass();
			}
		}

		if (_scenes.size() > 0) _scenes.front()->PostRender();

		// gui
		_gui->Begin();
		_conductor.Gui();
		_gui->DrawWidgets();
		_gui->End();

		// rendering complete
		_graphics->EndFrame();

	}

	EmbersEngine::~EmbersEngine() {

	}

}