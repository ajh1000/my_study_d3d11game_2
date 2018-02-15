#pragma once
/*
	����ڴ� �� Ŭ������ ��ӹް�, init, upate, render�Լ��� �������Ѵ�.
	main�Լ����� GameŬ������ ��ӹ��� Ŭ������ �����ϰ�, run�Լ��� try~catch ���̿� �����Ѵ�.

	Game Ŭ������ �ý��� Ŭ������. ���α׷��� ����� �� Game Ŭ������ �����Ǿ���ϰ�, ����ɶ�����
	Game Ŭ������ ������ �����ϰų� �������Ѽ��� �ȵȴ�. �ý��� Ŭ�������� ����ؾ��Ѵ�.
*/

#include "pch.h"

class Game
{
public:
	Game();
	virtual ~Game();

	virtual void init()=0;
	void run(unsigned int width, unsigned int height);

private:
	void Tick();

	void update();
	void render();


};

#ifdef _MSC_VER
#	pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif