#pragma once

#include <iostream>
#include <chrono>

class Timer {
public:
	void Start();
	void Stop();
	void Display();

	double ElapsedSecond();

private:
	std::chrono::steady_clock::time_point _start;
	std::chrono::steady_clock::time_point _end;
};

