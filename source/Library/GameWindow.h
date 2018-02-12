#pragma once


class GameWindow
{
public:
	GameWindow();
	~GameWindow();

	SINGLETON(GameWindow);

	void init(UINT width, UINT height);

	LRESULT CustomMsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HWND m_hWnd;
	HINSTANCE m_hInst;

#define BINDTYPE std::function<bool(UINT message, WPARAM wParam, LPARAM lParam)>
	void bindMsgWithCallbackFunc(DWORD msg, BINDTYPE func);

private:
	std::map<DWORD, std::vector<BINDTYPE>> m_mapBind;

};

