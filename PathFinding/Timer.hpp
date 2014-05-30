#ifndef TIMER_HPP
#define TIMER_HPP

#include <time.h>
#include <Windows.h>

namespace GejbEngine {
	class Timer {
	private:
		DWORD timerStart;
		mutable DWORD stopwatchStart;
	public:
		Timer(void);
		~Timer(void);
		void Timer::restart();
		DWORD getTimer() const;
		DWORD getStartTimerMillis() const;
		void sleep(int ms);
		void resetStopwatch();
		bool stopwatch(int ms) const;
	};
}

#endif