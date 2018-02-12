#pragma once

#include "Game.h"

class GameApp : public Game
{
public:
	GameApp();
	~GameApp() override;

	void init() override;
};

