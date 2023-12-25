#pragma once

namespace Core {

	class AppState {
	public:
		AppState() = default;
		~AppState() = default;
		virtual void Init() = 0;
		virtual void Tick(double dt) = 0;
	private:
	};

}