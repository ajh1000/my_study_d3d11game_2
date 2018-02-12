#pragma once
#include "pch.h"

class GameTimer
{
public:
	GameTimer();
	~GameTimer();

	SINGLETON(GameTimer);

	void init();

	void Tick(std::function<void()> Update);

	//��Ÿ Ÿ��
	float getDelta() { return m_elapsedTime; }

	// ���α׷� ���� �� �帥 �ð�.
	float getTotalElapsedTime();

	//GET FPS
	int getFPSCounts() { return m_framesPerSecond; }

	void setTargetFPS(int fps) { m_targetFPS = (float)fps; m_targetDelta = 1.f / fps; }
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
};
