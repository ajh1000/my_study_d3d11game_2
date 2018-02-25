#pragma once
#include "pch.h"

class GameWindow : public GameSingleton<GameWindow>
{
private:
#define BINDTYPE std::function<void(WPARAM wParam, LPARAM lParam)>

public:
	GameWindow();
	~GameWindow();

	void init(UINT width, UINT height);

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HWND m_hWnd;
	HINSTANCE m_hInst;

	//�ϳ��� �޼������� ���� �Ǳ� �ٶ�� �ϳ� �Ǵ� ���� ���� �Լ��� �߰��Ѵ�.
	void AddFuncToMsg(DWORD msg, BINDTYPE func);

private:
	LRESULT CustomMsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	std::map<DWORD, std::vector<BINDTYPE>> m_mapBind;

};

