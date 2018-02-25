#pragma once
#include "GameKeyCode.h"

class GameInput : public GameSingleton<GameInput>
{
private:
	struct KeyState {
		KeyState():isPressed(0),isHeld(0),isReleased(0),
			prevPressed(0), prevReleased(0) {}
		bool isPressed, isHeld, isReleased;
		bool prevPressed,prevReleased;
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

	//ex) "fire1" , "Jump" ... some kind of action name
	bool isActionPressed(std::string action);
	bool isActionHeld(std::string action);
	bool isActionReleased(std::string action);

	void setAction(std::string action,KeyCode keyCode);
private:
	void getInput(LPARAM lParam);

private:
	bool m_isAnyKeyPressed = false;
	//bool m_isPressed = false;
	//bool m_isPressing = false;
	//bool m_isReleased = false;

	unsigned char m_cntPressed = 0;
	unsigned char m_cntReleased = 0;

	std::vector<KeyState> m_arrKeyCodes;
	std::map<std::string,KeyCode > m_mapAction;
};

