#pragma once

#include "GameObject.h"
class GameTriangle : public GameObject
{
public:
	GameTriangle();
	~GameTriangle();

	void init() override;
	void update() override;

};

