#include "pch.h"
#include "GameTimer.h"

using namespace chrono;

/*
QueryPerformanceQuery / QueryPerformanceCounter 는 OS가 제공하는 기능이었지, C++ 에서 제공하는 표준 기능은 아니었다.
즉, 지금껏 C++ 표준의 고정밀 시간 계측 도구가 없었던 셈이다.

#헬퍼 타입들(chrono::seconds...)
이것들은 전부 인티져 타입의 값을 반환한다.

#duration_cast
time_point끼리 뺀 값을 duration_cast해줘야한다.
대부분의 경우 실수값을 원할태니 첫번째 인자에 float이나 double을, 그리고 두번째 인자에
ratio<> 템플릿을 입력하는데 아무것도 안적으면 ratio<1,1>로 입력된다. 이것은 초단위를 의미한다.
*/


GameTimer::GameTimer()
	: m_elapsedTotalTime(0),
	m_targetFPS(60),
	m_framesPerSecond(0),
	m_maxDelta(0.25f),// max frame time to avoid spiral of death
	m_targetDelta(0.016f),
	m_minDelta(0.00025f),
	m_isUpdated(false),
	m_secCounter(0),
	m_framesThisSecond(0),
	m_leftoverSecs(0),
	m_delta(0),
	m_elapsedTime(0),
	m_isLog(0)

{
	m_last = high_resolution_clock::now();

	m_targetDelta = 1.f / m_targetFPS;
	m_elapsedTime = m_targetDelta;
}

GameTimer::~GameTimer()
{

}

void GameTimer::init()
{
}

void GameTimer::Tick(std::function<void()> Update)
{
	high_resolution_clock::time_point current = high_resolution_clock::now();
	duration<float> deltaDuration = duration_cast<duration<float>>(current - m_last);
	m_last = current;

	m_isUpdated = false;

	m_delta = deltaDuration.count();


	if (m_delta >= m_maxDelta) {
		m_delta = m_maxDelta;
	}

	if (abs(m_delta - m_targetDelta) < m_minDelta) {
		m_delta = m_targetDelta;
	}

	m_secCounter += m_delta;
	m_leftoverSecs += m_delta;

	while (m_leftoverSecs >= m_targetDelta) {
		m_elapsedTime = m_targetDelta;
		m_isUpdated = true;
		m_elapsedTotalTime += m_targetDelta;
		m_leftoverSecs -= m_targetDelta;

		Update();
	}

	if (m_isUpdated == true) {
		m_framesThisSecond++;
	}

	if (m_secCounter >= 1.0f)
	{
		m_framesPerSecond = m_framesThisSecond;
		m_framesThisSecond = 0;
		m_secCounter = 0;

#ifdef _DEBUG
		if (m_isLog == true) {
			cout << "total : " << getTotalElapsedTime() << endl;
			cout << "delta : " << getDelta() << endl;
			cout << "fps : " << getFPSCounts() << endl;
		}
#endif
	}

}

float GameTimer::getTotalElapsedTime()
{

	float totalTime = m_elapsedTotalTime;
	UINT integerPart = static_cast<UINT>(totalTime);

	if (totalTime + 0.1f >= integerPart + 1.f) {
		totalTime = static_cast<float>(integerPart + 1);
	}
	else {
		totalTime = static_cast<float>(integerPart);
	}

	m_elapsedTotalTime = totalTime;

	return m_elapsedTotalTime;
}

