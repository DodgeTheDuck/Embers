#pragma once

#include "Core/app_state.h"

class StateEngineDev : public Core::AppState {
	void Init() override;
	void Tick() override;
	void Render() override;
};