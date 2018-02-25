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

	//outState==0 means button downed, outState==1 means button released.
	void analyzeMouseState(unsigned short &input,  bool &outState, KeyCode &outKey);
private:
	bool m_isPaused = false;
	bool m_isAnyKeyPressed = false;

	std::vector<KeyState> m_arrKeyCodes;
	std::vector<KeyState> m_arrReserve;
	std::map<std::string,KeyCode > m_mapAction;

	signed short m_wheelValue;
	long m_mouseX, m_mouseY;

	unsigned char m_arrSize;
};

