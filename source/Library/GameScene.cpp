#include "pch.h"
#include "GameScene.h"


GameScene::GameScene()
{
}


GameScene::~GameScene()
{
}

void GameScene::add(std::shared_ptr< GameObject > obj)
{
	obj->init();
	m_GameObectArr.push_back(obj);
}

void GameScene::update()
{
	for (auto& o : m_GameObectArr) {
		o->update();
	}
}

void GameScene::render()
{
	for (auto& o : m_GameObectArr) {
		o->render();
	}
}

