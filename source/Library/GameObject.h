#pragma once

#include "GameDevice.h"
#include "GameTimer.h"

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void init()=0;

protected:
};


/*
	device
	context
	timer
	inputDesc,effects
	model import
*/