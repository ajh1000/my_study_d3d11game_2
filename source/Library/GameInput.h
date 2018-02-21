#pragma once
#include "GameSingleton.h"

class GameInput : public GameSingleton<GameInput>
{
public:
	GameInput();
	~GameInput();

	void init();
	void update();

	bool m_isPressed = false;
	bool m_isPressing = false;
	bool m_isReleased = false;

	unsigned char m_counterPressed = 0;
	unsigned char m_counterReleased = 0;
};

