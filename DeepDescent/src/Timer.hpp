#pragma once
#include "raylib.h"

class Timer {
public:
	bool running = false;
	double startTime = 0;
	double currentTime = 0;
	double duration = 0; // in seconds
public:
	inline Timer(const double& d) : 
		duration(d) {}

	inline void Start() {
		startTime = GetTime();
		running = true;
	}

	inline void Stop() {
		running = false;
	}

	// returns false if not running or time not elapsed
	inline bool Check() {
		if (!running) return false;
		
		currentTime = GetTime();
		if (currentTime - startTime >= duration) {
			startTime = currentTime;
			return true;
		}
		else {
			return false;
		}

	}

	inline void Reset() {
		startTime = 0;
		currentTime = 0;
		running = false;
	}

	inline void SetDuration(const double& d) {
		duration = d;
	}

};