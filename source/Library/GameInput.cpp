#include "pch.h"
#include "GameInput.h"
#include "GameWindow.h"
#include <hidsdi.h>

GameInput::GameInput()
	:m_mouseDeltaX(0), m_mouseDeltaY(0), m_wheelValue(0),
	m_isAnyKeyPressed(false), m_arrSize(255)

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
	Rid[1].hwndTarget =GameWindow::instance().m_hWnd;

	if (RegisterRawInputDevices(Rid, 2, sizeof(Rid[0])) == FALSE) {
		throw std::exception("registration failed");
	}


	GameWindow::instance().AddFuncToMsg(WM_INPUT, [&](WPARAM wParam, LPARAM lParam) {
		this->getInput(lParam);
	});

	GameWindow::instance().AddFuncToMsg(WM_SETFOCUS, [&](WPARAM wParam, LPARAM lParam) {
		//m_arrKeyCodes.assign(m_arrReserve.begin(), m_arrReserve.end());
	});

	GameWindow::instance().AddFuncToMsg(WM_KILLFOCUS, [&](WPARAM wParam, LPARAM lParam) {
		//m_arrReserve.assign(m_arrKeyCodes.begin(), m_arrKeyCodes.end());

		ZeroMemory(m_arrKeyCodes.data(), sizeof(KeyState)*m_arrSize);
	});


	//pre-defined actions
	setAction("fire1", KeyCode::LBUTTON);
	setAction("fire2", KeyCode::RBUTTON);
}

void GameInput::update()
{
	//check pressed&released state at the begging of the frame. 
	for (auto &o : m_arrKeyCodes)
	{
		if (o.isPressed == true) {
			if (o.prevPressed == true) {
				o.isPressed = false;
				m_isAnyKeyPressed = false;
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
			m_arrKeyCodes[key].isHeld = false;
			m_arrKeyCodes[key].isReleased = true;
		}
	}

	if (raw->header.dwType == RIM_TYPEMOUSE) {
		unsigned short rawState = raw->data.mouse.usButtonFlags;

		m_mouseDeltaX = raw->data.mouse.lLastX;
		m_mouseDeltaY = raw->data.mouse.lLastY;

		if (rawState == RI_MOUSE_WHEEL) {
			m_wheelValue = static_cast<signed short>(raw->data.mouse.usButtonData);
		}
		else {
			analyzeMouseState(rawState, m_arrMouseState);

			for (auto &mouse : m_arrMouseState) {
				if (mouse.state == 0) {
					if (m_arrKeyCodes[mouse.key].isHeld == true) {
						m_arrKeyCodes[mouse.key].isPressed = false;
					}
					else {
						m_arrKeyCodes[mouse.key].isPressed = true;
					}

					m_isAnyKeyPressed = true;
					m_arrKeyCodes[mouse.key].isHeld = true;
					m_arrKeyCodes[mouse.key].isReleased = false;
				}
				else {
					m_arrKeyCodes[mouse.key].isHeld = false;
					m_arrKeyCodes[mouse.key].isReleased = true;
				}
			}
		}
	}
}

void GameInput::analyzeMouseState(unsigned short &input, std::vector<MouseState> &outStates)
{
	outStates.clear();
	MouseState mouse;

	//LBUTTON
	if (input&RI_MOUSE_LEFT_BUTTON_DOWN) {
		mouse.state = 0;
		mouse.key = KeyCode::LBUTTON;
		outStates.push_back(mouse);
	}
	if (input&RI_MOUSE_LEFT_BUTTON_UP) {
		mouse.state = 1;
		mouse.key = KeyCode::LBUTTON;
		outStates.push_back(mouse);
	}

	//RBUTTON
	if (input&RI_MOUSE_RIGHT_BUTTON_DOWN) {
		mouse.state = 0;
		mouse.key = KeyCode::RBUTTON;
		outStates.push_back(mouse);
	}
	if (input&RI_MOUSE_RIGHT_BUTTON_UP) {
		mouse.state = 1;
		mouse.key = KeyCode::RBUTTON;
		outStates.push_back(mouse);
	}

	//MBUTTON
	if (input&RI_MOUSE_MIDDLE_BUTTON_DOWN) {
		mouse.state = 0;
		mouse.key = KeyCode::MBUTTON;
		outStates.push_back(mouse);
	}
	if (input&RI_MOUSE_MIDDLE_BUTTON_UP) {
		mouse.state = 1;
		mouse.key = KeyCode::MBUTTON;
		outStates.push_back(mouse);
	}

	//X1BUTTON
	if (input&RI_MOUSE_BUTTON_4_DOWN) {
		mouse.state = 0;
		mouse.key = KeyCode::X1BUTTON;
		outStates.push_back(mouse);
	}
	if (input&RI_MOUSE_BUTTON_4_UP) {
		mouse.state = 1;
		mouse.key = KeyCode::X1BUTTON;
		outStates.push_back(mouse);
	}

	//X2BUTTON
	if (input&RI_MOUSE_BUTTON_5_DOWN) {
		mouse.state = 0;
		mouse.key = KeyCode::X2BUTTON;
		outStates.push_back(mouse);
	}
	if (input&RI_MOUSE_BUTTON_5_UP) {
		mouse.state = 1;
		mouse.key = KeyCode::X2BUTTON;
		outStates.push_back(mouse);
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