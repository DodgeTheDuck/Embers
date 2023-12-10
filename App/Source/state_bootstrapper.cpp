#include "stdafx.h"
#include "state_bootstrapper.h"
#include "state_engine_dev.h"
#include "Core/engine.h"

enum DevMode
{
	EngineDev
};

void StateBootsrapper::Init()
{
	
	DevMode devModeToRun = DevMode::EngineDev;

	std::map<DevMode, std::shared_ptr<AppState>> devTests = {
		{DevMode::EngineDev, std::make_shared<StateEngineDev>()}
	};
	 
	Core::Engine().PushAppState(devTests[devModeToRun]);

}

void StateBootsrapper::Tick()
{
}

void StateBootsrapper::Render()
{
}
