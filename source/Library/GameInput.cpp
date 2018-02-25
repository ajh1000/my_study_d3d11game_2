#include "pch.h"
#include "GameInput.h"
#include "GameWindow.h"
#include <hidsdi.h>

GameInput::GameInput()
	:m_mouseX(0), m_mouseY(0), m_wheelValue(0),
	 m_isAnyKeyPressed(false), m_isPaused(false), m_arrSize(255)

{
	m_arrKeyCodes.clear();
	m_arrKeyCodes.resize(m_arrSize);
	m_mapAction.clear();
}


GameInput::~GameInput()
{
}

void GameInput::init()
{
	//Most Windows applications depend on those legacy messages in order to operate correctly. 
	//If your application is not a fullscreen application RIDEV_NOLEGACY is not a good idea to use.
	//info link : https://stackoverflow.com/a/20643589

	RAWINPUTDEVICE Rid[2];

	//KEYBOARD
	Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
	Rid[0].usUsage = HID_USAGE_GENERIC_KEYBOARD;
	Rid[0].dwFlags = 0;
	Rid[0].hwndTarget = GameWindow::instance().m_hWnd;

	//MOUSE
	Rid[1].usUsagePage = HID_USAGE_PAGE_GENERIC;
	Rid[1].usUsage = HID_USAGE_GENERIC_MOUSE;
	Rid[1].dwFlags = 0;
	Rid[1].hwndTarget = GameWindow::instance().m_hWnd;

	if (RegisterRawInputDevices(Rid, 2, sizeof(Rid[0])) == FALSE) {
		throw std::exception("registration failed");
	}


	GameWindow::instance().AddFuncToMsg(WM_INPUT, [&](WPARAM wParam, LPARAM lParam) {
			this->getInput(lParam);
	});

	GameWindow::instance().AddFuncToMsg(WM_SETFOCUS, [&](WPARAM wParam, LPARAM lParam) {
		m_arrKeyCodes.assign(m_arrReserve.begin(), m_arrReserve.end());
	});

	GameWindow::instance().AddFuncToMsg(WM_KILLFOCUS, [&](WPARAM wParam, LPARAM lParam) {
		m_arrReserve.assign(m_arrKeyCodes.begin(), m_arrKeyCodes.end());

		ZeroMemory(m_arrKeyCodes.data(), sizeof(KeyState)*m_arrSize);
	});


	//pre-defined actions
	setAction("fire1", KeyCode::LBUTTON);
	setAction("fire2", KeyCode::RBUTTON);
}

void GameInput::update()
{
	//check pressed&released state. only available at current frame.
		for (auto &o : m_arrKeyCodes)
		{
			if (o.isPressed == true) {
				if (o.prevPressed == true) {
					o.isPressed = false;
				}
			}

			if (o.isReleased == true) {
				if (o.prevReleased == true) {
					o.isReleased = false;
				}
			}

			o.prevPressed = o.isPressed;
			o.prevReleased = o.isReleased;
		}
	

}


void GameInput::getInput(LPARAM lParam)
{
	UINT size = 40;
	BYTE data[40];
	ZeroMemory(data, size);

	GetRawInputData((HRAWINPUT)lParam, RID_INPUT, data, &size,
		sizeof(RAWINPUTHEADER));

	RAWINPUT* raw = (RAWINPUT*)&data;

	if (raw->header.dwType == RIM_TYPEKEYBOARD)
	{
		unsigned char key = static_cast<unsigned char>(raw->data.keyboard.VKey);

		if (raw->data.keyboard.Flags == 0) {
			if (m_arrKeyCodes[key].isHeld == true) {
				m_arrKeyCodes[key].isPressed = false;
			}
			else {
				m_arrKeyCodes[key].isPressed = true;
			}

			m_isAnyKeyPressed = true;
			m_arrKeyCodes[key].isHeld = true;
			m_arrKeyCodes[key].isReleased = false;
		}
		else {
			m_isAnyKeyPressed = false;
			m_arrKeyCodes[key].isHeld = false;
			m_arrKeyCodes[key].isReleased = true;
		}
	}

	if (raw->header.dwType == RIM_TYPEMOUSE) {
		unsigned short rawState = raw->data.mouse.usButtonFlags;

		m_mouseX = raw->data.mouse.lLastX;
		m_mouseY = raw->data.mouse.lLastY;


		if (rawState == RI_MOUSE_WHEEL) {
			m_wheelValue = static_cast<signed short>(raw->data.mouse.usButtonData);
		}
		else {
			bool state;
			KeyCode key;
			analyzeMouseState(rawState, state, key);

			//마우스 왼쪽,오른쪽 동시에 눌르면 5
			//동시에 풀으면 10
			//어떻게 처리해야하나

			if (key != KeyCode::None)
			{
				if (state == 0) {
					if (m_arrKeyCodes[key].isHeld == true) {
						m_arrKeyCodes[key].isPressed = false;
					}
					else {
						m_arrKeyCodes[key].isPressed = true;
					}

					m_isAnyKeyPressed = true;
					m_arrKeyCodes[key].isHeld = true;
					m_arrKeyCodes[key].isReleased = false;
				}
				else {
					m_isAnyKeyPressed = false;
					m_arrKeyCodes[key].isHeld = false;
					m_arrKeyCodes[key].isReleased = true;
				}
			}
		}



	}
}

void GameInput::analyzeMouseState(unsigned short & input, bool & outState, KeyCode & outKey)
{
	switch (input) {
	case RI_MOUSE_LEFT_BUTTON_DOWN:
		outState = 0;
		outKey = KeyCode::LBUTTON;
		break;
	case RI_MOUSE_LEFT_BUTTON_UP:
		outState = 1;
		outKey = KeyCode::LBUTTON;
		break;

	case RI_MOUSE_RIGHT_BUTTON_DOWN:
		outState = 0;
		outKey = KeyCode::RBUTTON;
		break;
	case RI_MOUSE_RIGHT_BUTTON_UP:
		outState = 1;
		outKey = KeyCode::RBUTTON;
		break;

	case RI_MOUSE_MIDDLE_BUTTON_DOWN:
		outState = 0;
		outKey = KeyCode::MBUTTON;
		break;
	case RI_MOUSE_MIDDLE_BUTTON_UP:
		outState = 1;
		outKey = KeyCode::MBUTTON;
		break;

	case RI_MOUSE_BUTTON_4_DOWN:
		outState = 0;
		outKey = KeyCode::X1BUTTON;
		break;
	case RI_MOUSE_BUTTON_4_UP:
		outState = 1;
		outKey = KeyCode::X1BUTTON;
		break;

	case RI_MOUSE_BUTTON_5_DOWN:
		outState = 0;
		outKey = KeyCode::X2BUTTON;
		break;
	case RI_MOUSE_BUTTON_5_UP:
		outState = 1;
		outKey = KeyCode::X2BUTTON;
		break;


	default:
		outState = 0;
		outKey = KeyCode::None;
		break;
	}
}


bool GameInput::isAnyKeyPressed()
{
	return m_isAnyKeyPressed;
}
bool GameInput::isKeyPressed(KeyCode keyCode)
{
	return m_arrKeyCodes[keyCode].isPressed;
}
bool GameInput::isKeyHeld(KeyCode keyCode)
{
	return m_arrKeyCodes[keyCode].isHeld;
}
bool GameInput::isKeyReleased(KeyCode keyCode)
{
	return m_arrKeyCodes[keyCode].isReleased;
}


bool GameInput::isActionPressed(std::string action)
{
	return m_arrKeyCodes[m_mapAction[action]].isPressed;
}
bool GameInput::isActionHeld(std::string action)
{
	return m_arrKeyCodes[m_mapAction[action]].isHeld;
}
bool GameInput::isActionReleased(std::string action)
{
	return m_arrKeyCodes[m_mapAction[action]].isReleased;
}

void GameInput::setAction(std::string action, KeyCode keyCode)
{
	m_mapAction[action] = keyCode;
}




//#backup codes
//unsigned char key = MapVirtualKey(raw->data.keyboard.VKey, MAPVK_VK_TO_CHAR);