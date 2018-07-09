#pragma once

#include "pch.h"

class GameScene;

class Game
{
public:
	Game();
	virtual ~Game();

	virtual void init()=0;
	void run(unsigned int width, unsigned int height);

	void addScene(const char* sceneName, shared_ptr<GameScene> scene);
	void setScene(shared_ptr<GameScene> scene);
	void setScene(const char* sceneName);
private:
	void Tick();

	void update();
	void render();

private:
	shared_ptr<GameScene> m_scene;
	map < string, shared_ptr<GameScene>> m_mapScene;

	bool m_quit = false;
};

#ifdef _MSC_VER
#	pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif