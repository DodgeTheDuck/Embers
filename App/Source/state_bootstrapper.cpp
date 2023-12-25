#include "stdafx.h"
#include "state_bootstrapper.h"
#include "state_engine_dev.h"
#include "state_particle_dev.h"
#include <core/engine/engine.h>
#include <core/base.h>

enum DevMode
{
	EngineDev,
	ParticleDev
};

void StateBootsrapper::Init()
{
	
	DevMode devModeToRun = DevMode::EngineDev;

	std::map<DevMode, Core::Ref<AppState>> devTests = {
		{DevMode::EngineDev, std::make_shared<StateEngineDev>()},
		{DevMode::ParticleDev, std::make_shared<StateParticleDev>()}
	};
	 
	Core::Engine().PushAndInitAppState(devTests[devModeToRun]);

}

void StateBootsrapper::Tick()
{
}

void StateBootsrapper::Render()
{
}
