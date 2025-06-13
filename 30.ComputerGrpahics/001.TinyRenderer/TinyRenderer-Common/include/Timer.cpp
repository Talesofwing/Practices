#include "Timer.h"

void Timer::Start() {
	_start = std::chrono::high_resolution_clock::now();
}

void Timer::Stop() {
	_end = std::chrono::high_resolution_clock::now();
}

void Timer::Display() {
	std::cout << "Elapsed Time: " << ElapsedSecond() << "(s)" << std::endl;
}

double Timer::ElapsedSecond() {
	std::chrono::duration<double> elapsed = _end - _start;
	return elapsed.count();
}
