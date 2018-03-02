#pragma once
#include "GameKeyCode.h"


class GameInput : public GameSingleton<GameInput>
{
private:
	//Ű����, ���콺 �Է� ���� ���� ����ü.
	struct KeyState {
		KeyState():isPressed(0),isHeld(0),isReleased(0),
			prevPressed(0), prevReleased(0) {}
		bool isPressed, isHeld, isReleased;
		bool prevPressed,prevReleased;
	};

	//���콺 �Է��� Bit ������ �Է°��� �����⶧����, ������ bit���� �ش��ϴ� �Է� ������ ������ �� �ֵ��� �Ͽ���.
	struct MouseState {
		MouseState() : state(false),key(KeyCode::None){}
		//state==0 means button downed, state==1 means button released.
		bool state;
		KeyCode key;
	};

public:
	GameInput();
	~GameInput();

	void init();
	void update();

	bool isAnyKeyPressed();
	
	bool isKeyPressed(KeyCode keyCode);
	bool isKeyHeld(KeyCode keyCode);
	bool isKeyReleased(KeyCode keyCode);

	bool isActionPressed(std::string action);
	bool isActionHeld(std::string action);
	bool isActionReleased(std::string action);

	//ex) "fire1" , "Jump" ... some kind of action name
	void setAction(std::string action,KeyCode keyCode);
private:
	void getInput(LPARAM lParam);

	void analyzeMouseState(unsigned short &input,std::vector<MouseState> &outStates);
private:
	bool m_isAnyKeyPressed = false;

	unsigned char m_arrSize=255;

	//Keyboard&Mouse states
	std::vector<KeyState> m_arrKeyCodes;
	
	//copy from m_arrKeyCodes when app is paused
	std::vector<KeyState> m_arrReserve;

	//Mouse INFOs...
	std::vector<MouseState> m_arrMouseState;
	signed short m_wheelValue;
	long m_mouseDeltaX, m_mouseDeltaY;

	//Action Array
	std::map<std::string, KeyCode > m_mapAction;

	
};

