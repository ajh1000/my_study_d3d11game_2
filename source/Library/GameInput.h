#pragma once
#include "GameSingleton.h"

class GameInput : public GameSingleton<GameInput>
{
public:
	enum KeyCode {

	};

public:
	GameInput();
	~GameInput();

	void init();
	void update();

	
	void isKeyPressed(KeyCode keyCode);
	void isKeyHeld(KeyCode keyCode);
	void isKeyReleased(KeyCode keyCode);

	//ex) "fire1" , "Jump" ... some kind of action name
	void isActionPressed(std::string action);
	void isActionHeld(std::string action);
	void isActionReleased(std::string action);
private:
	void getInput(LPARAM lParam);

	//Pressed, Released 판정 관리 함수
	void checkPressedReleased();
private:
	bool m_isPressed = false;
	bool m_isPressing = false;
	bool m_isReleased = false;

	unsigned char m_cntPressed = 0;
	unsigned char m_cntReleased = 0;
};

