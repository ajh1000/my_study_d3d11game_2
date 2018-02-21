#include "pch.h"
#include "GameInput.h"
#include <hidsdi.h>
#include "GameWindow.h"

GameInput::GameInput()
	:m_counterPressed(0),
	m_counterReleased(0)
{
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


	GameWindow::instance().AddFuncToMsg(WM_INPUT, [&](WPARAM wParam, LPARAM lParam)->bool {

		UINT size = 40;
		BYTE data[40];
		ZeroMemory(data, size);

		GetRawInputData((HRAWINPUT)lParam, RID_INPUT, data, &size,
			sizeof(RAWINPUTHEADER));

		RAWINPUT* raw = (RAWINPUT*)&data;

		if (raw->header.dwType == RIM_TYPEKEYBOARD)
		{
			if (raw->data.keyboard.Flags == 0) {
				if (m_isPressing==true) {
					m_isPressed = false;
				}
				else {
					m_isPressed = true;
				}
				
				m_isPressing = true;
				m_isReleased = false;
			}
			else {
				m_isPressing = false;
				m_isReleased = true;
			}
		}

		return true;
	});

}

void GameInput::update()
{
	if (m_isPressed == true) {
		m_counterPressed += 1;
		
		if (m_counterPressed >= 2) {
			m_isPressed = false;
			m_counterPressed = 0;
		}
	}

	if (m_isReleased == true) {
		m_counterReleased += 1;
		
		if (m_counterReleased >= 2) {
			m_isReleased = false;
			m_counterReleased = 0;
		}
	}
}
