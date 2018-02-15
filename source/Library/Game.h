#pragma once
/*
	사용자는 이 클래스를 상속받고, init, upate, render함수를 재정의한다.
	main함수에는 Game클래스를 상속받은 클래스를 생성하고, run함수를 try~catch 사이에 실행한다.

	Game 클래스는 시스템 클래스다. 프로그램이 실행될 때 Game 클래스가 생성되어야하고, 종료될때까지
	Game 클래스를 여러개 생성하거나 삭제시켜서는 안된다. 시스템 클래스임을 명심해야한다.
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