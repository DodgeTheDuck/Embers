#pragma once

#include "Core/engine/app_state.h"

namespace Flare {

	class StateBootsrapper : public Core::AppState {
	public:
		void Init() override;
		void Tick(double dt) override;
	};

}