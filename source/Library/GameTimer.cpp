#include "pch.h"
#include "GameTimer.h"

using namespace chrono;

/*
QueryPerformanceQuery / QueryPerformanceCounter �� OS�� �����ϴ� ����̾���, C++ ���� �����ϴ� ǥ�� ����� �ƴϾ���.
��, ���ݲ� C++ ǥ���� ������ �ð� ���� ������ ������ ���̴�.

#���� Ÿ�Ե�(chrono::seconds...)
�̰͵��� ���� ��Ƽ�� Ÿ���� ���� ��ȯ�Ѵ�.

#duration_cast
time_point���� �� ���� duration_cast������Ѵ�.
��κ��� ��� �Ǽ����� �����´� ù��° ���ڿ� float�̳� double��, �׸��� �ι�° ���ڿ�
ratio<> ���ø��� �Է��ϴµ� �ƹ��͵� �������� ratio<1,1>�� �Էµȴ�. �̰��� �ʴ����� �ǹ��Ѵ�.
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
	m_elapsedTime(0)

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
		cout << "total : " << getTotalElapsedTime() << endl;
		cout << "delta : " << getDelta() << endl;
		cout << "fps : " << getFPSCounts() << endl;
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

