#pragma once

namespace Core {
	using namespace std::chrono;

	typedef uint32_t conductor_timer;

	class Conductor {

		struct Timer {
			Timer() = default;
			Timer(std::string name, double freqMs) : freqMs(freqMs), name(name) {
				timeLastQuery = high_resolution_clock::now();
			};
			std::string name{};
			double freqMs{};
			double counter{};
			unsigned int accumulator{};
			unsigned int total{};
			steady_clock::time_point timeLastQuery;
		};

	public:
		void Init();
		void Tick();
		bool Query(const conductor_timer timerId, double& delta);
		void Gui();

		conductor_timer CreateTimer(const char* name, const double freqMs);

	private:
		std::vector<Timer> _timers;
		steady_clock::time_point _timeLastTick;
		double _secAccumulator;

	};

}