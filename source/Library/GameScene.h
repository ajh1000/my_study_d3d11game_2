#pragma once
#include "pch.h"
#include "GameObject.h"

class GameScene
{
public:
	GameScene();
	~GameScene();

	virtual void init() = 0;
	void update();
	void render();

protected:
	//add and automatically calls init()
	void add(std::shared_ptr< GameObject > obj);

private:
	std::vector<std::shared_ptr< GameObject>> m_GameObectArr;
};

