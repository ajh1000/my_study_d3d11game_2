#pragma once
#include "pch.h"

class GameTimer  : public GameSingleton<GameTimer>
{
public:
	enum METHOD {
		FixedTimer=0,
		VariableTimer
	};
public:
	GameTimer();
	~GameTimer();

	void init(METHOD type);

	std::function<void(std::function<void()> update)> Tick;

	float getDelta() { return m_elapsedTime; }
	float getTotalElapsedTime();
	int getFPSCounts() { return m_framesPerSecond; }
	METHOD getTimerMethod() { return m_method; }

	void setTargetFPS(int fps) { m_targetFPS = (float)fps; m_targetDelta = 1.f / fps; }

private:
	void fixedTick(std::function<void()> &update);

private:
	std::chrono::high_resolution_clock::time_point m_last;
	float m_delta = 0;
	float m_elapsedTime = 0;
	float m_elapsedTotalTime = 0;
	float m_targetFPS = 60;
	int m_framesPerSecond = 0;
	int m_framesThisSecond = 0;
	float m_maxDelta = 0.1f; //1 / 10.f
	float m_minDelta = 0.00025f; // 0.001 / 4.f
	float m_targetDelta = 0.016f; //default to 60fps-0.016sec.

	bool m_isUpdated = false;
	float m_secCounter = 0;
	float m_leftoverSecs = 0;

	bool m_isLog = true;

	METHOD m_method;
};
