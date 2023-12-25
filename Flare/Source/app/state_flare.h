#pragma once

namespace Flare {

	class StateFlare : public Core::AppState {

	public:
		void Init() override;
		void Tick(double dt) override;

	};

}