#pragma once
#include <Windows.h>
class FrameTimer
{
public:
	void init(int);
	int framesToUpdate();

private:
	LARGE_INTEGER timerFreq;
	LARGE_INTEGER timeNow;
	LARGE_INTEGER timePrevious;
	int Requested_FPS;
	float intervalsPerFrame;
	float intervalsSinceLastUpdate;
};