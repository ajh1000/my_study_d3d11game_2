#include "SceneTitle.h"

#include "GameTriangle.h"

SceneTitle::SceneTitle()
{
}


SceneTitle::~SceneTitle()
{
}

void SceneTitle::init()
{
	add(make_shared<GameTriangle>());
}
