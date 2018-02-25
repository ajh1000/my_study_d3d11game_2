#include "pch.h"
#include "GameInput.h"
#include "GameWindow.h"
#include <hidsdi.h>

GameInput::GameInput()
	:m_cntPressed(0),
	m_cntReleased(0)
{
	m_arrKeyCodes.clear();
	m_arrKeyCodes.resize(255);
	m_mapAction.clear();
}


GameInput::~GameInput()
{
}

void GameInput::init()
{
	RAWINPUTDEVICE Rid;

	Rid.usUsagePage = HID_USAGE_PAGE_GENERIC;
	Rid.usUsage = HID_USAGE_GENERIC_KEYBOARD;
	Rid.dwFlags = RIDEV_NOLEGACY;
	Rid.hwndTarget = GameWindow::instance().m_hWnd;

	if (RegisterRawInputDevices(&Rid, 1, sizeof(RAWINPUTDEVICE)) == FALSE) {
		throw std::exception("registration failed");
	}


	GameWindow::instance().AddFuncToMsg(WM_INPUT, [&](WPARAM wParam, LPARAM lParam) {
		this->getInput(lParam);
	});

	//register pre-built commands 
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