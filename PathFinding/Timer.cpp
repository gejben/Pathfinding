

#include "Timer.hpp"

namespace GejbEngine {
	Timer::Timer(void) {
		timerStart = timeGetTime();
		resetStopwatch();
	}

	Timer::~Timer() {
	}

	void Timer::restart() {
		timerStart = timeGetTime();
		resetStopwatch();
	}

	DWORD Timer::getTimer() const{
		return (DWORD)(timeGetTime());
	}

	DWORD Timer::getStartTimerMillis() const{
		return (DWORD)(timeGetTime() - timerStart);
	}

	void Timer::sleep(int ms) {
		DWORD start = getTimer();
		while(start + ms > getTimer());
	}

	void Timer::resetStopwatch() {
		stopwatchStart = getTimer();
	}

	bool Timer::stopwatch(int ms) const{
		if(timeGetTime() > stopwatchStart + ms) {
			stopwatchStart = getTimer();
			return true;
		}
		return false;
	}
}