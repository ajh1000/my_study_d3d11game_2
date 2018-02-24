#include "pch.h"
#include "GameInput.h"
#include <hidsdi.h>
#include "GameWindow.h"

GameInput::GameInput()
	:m_cntPressed(0),
	m_cntReleased(0)
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


	GameWindow::instance().AddFuncToMsg(WM_INPUT, [&](WPARAM wParam, LPARAM lParam) {
		this->getInput(lParam);
	});

}

void GameInput::update()
{
	checkPressedReleased();


}
void GameInput::isKeyPressed(KeyCode keyCode)
{
}
void GameInput::isKeyHeld(KeyCode keyCode)
{
}
void GameInput::isKeyReleased(KeyCode keyCode)
{
}
void GameInput::isActionPressed(std::string action)
{
}
void GameInput::isActionHeld(std::string action)
{
}
void GameInput::isActionReleased(std::string action)
{

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
		unsigned char key = MapVirtualKey(raw->data.keyboard.VKey, MAPVK_VK_TO_CHAR);

		if (raw->data.keyboard.Flags == 0) {
			if (m_isPressing == true) {
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
}

void GameInput::checkPressedReleased()
{
	//m_cntXXXXXX 변수를 둔 이유 :
	//이번 프레임에서만 눌렀다/땠다 이벤트를 발생시킴.
	//다음 프레임에서는 눌렀다/땠다 이벤트를 종료시킴.

	if (m_isPressed == true) {
		m_cntPressed += 1;

		if (m_cntPressed >= 2) {
			m_isPressed = false;
			m_cntPressed = 0;
		}
	}

	if (m_isReleased == true) {
		m_cntReleased += 1;

		if (m_cntReleased >= 2) {
			m_isReleased = false;
			m_cntReleased = 0;
		}
	}
}
/*
using UnityEngine;

public class KeyCodeExample : MonoBehaviour
{
	void Update()
	{
		if (Input.GetKeyDown(KeyCode.Space))
			Debug.Log("Space key was pressed.");

		if (Input.GetKeyUp(KeyCode.Space))
			Debug.Log("Space key was released.");

			myTime = myTime + Time.deltaTime;

			//held down
		if (Input.GetButton("Fire1") && myTime > nextFire)
		{
			nextFire = myTime + fireDelta;
			newProjectile = Instantiate(projectile, transform.position, transform.rotation) as GameObject;

			// create code here that animates the newProjectile

			nextFire = nextFire - myTime;
			myTime = 0.0F;
		}
		//Input.GetButtonDown <- pressed once
		//Input.GetAxis
	}


}
*/