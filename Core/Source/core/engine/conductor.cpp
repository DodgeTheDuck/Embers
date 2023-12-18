#include <stdafx.h>
#include <core/engine/conductor.h>

namespace Core {

	using namespace std::chrono;

	void Conductor::Init() {
		// initialise last time to now to have a sort of decent reference point at startup
		_timeLastTick = high_resolution_clock::now();
	}

	void Conductor::Tick()
	{

		// current time
		const auto now = high_resolution_clock::now();
		const duration<double, std::milli> deltaMs = now - _timeLastTick;

		// update our second timer
		_secAccumulator += deltaMs.count();

		// update each timer
		for (auto& timer : _timers) {
			if (_secAccumulator >= 1000.0) {
				timer.total = timer.accumulator;
				timer.accumulator = 0;
			}
			timer.counter += deltaMs.count();
		}

		// reset second timer if needed
		if (_secAccumulator >= 1000.0) {
			_secAccumulator -= 1000.0;
		}

		// finally, get ready for next tick
		_timeLastTick = now;
	}

	bool Conductor::Query(const conductor_timer timerId, double& delta)
	{
		// why does timing stuff always have to look so ugly
		auto& timer = _timers[timerId];
		if (timer.counter >= timer.freqMs) {
			timer.counter -= timer.freqMs;
			const auto now = high_resolution_clock::now();
			const duration<double> deltaS = now - timer.timeLastQuery;
			delta = deltaS.count();
			timer.timeLastQuery = now;
			timer.accumulator++;
			return true;
		}
		return false;
	}

	void Conductor::Gui()
	{
		ImGui::Begin("Performance");
		for (const auto& timer : _timers) {
			ImGui::Text((timer.name + ": " + std::to_string(timer.total)).c_str());
		}
		ImGui::End();
	}

	conductor_timer Conductor::CreateTimer(const char* name, const double freqMs) {
		_timers.push_back(Timer(name, freqMs));
		return _timers.size() - 1;
	}

}