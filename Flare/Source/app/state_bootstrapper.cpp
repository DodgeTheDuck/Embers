#include "stdafx.h"
#include "state_bootstrapper.h"
#include "state_flare.h"
#include <core/engine/engine.h>
#include <core/base.h>

namespace Flare {

	void StateBootsrapper::Init()
	{
		Core::Engine().PushAppState(CreateRef<StateFlare>());
	}

	void StateBootsrapper::Tick(double dt)
	{
	}	

}