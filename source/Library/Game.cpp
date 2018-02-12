#include "pch.h"
#include "Game.h"

#include "GameWindow.h"
#include "GameDevice.h"
#include "GameTimer.h"

Game::Game()
{
}


Game::~Game()
{

}


void Game::Tick()
{
	GameTimer::instance().Tick([&]() {
		update();
	});

	render();

}

void Game::update()
{

}

void Game::render()
{
	GameDevice::instance().m_context->ClearRenderTargetView(GameDevice::instance().m_renderTargetView.Get(),
		DirectX::Colors::Aquamarine);
	GameDevice::instance().m_context->ClearDepthStencilView(GameDevice::instance().m_depthStencilView.Get(),
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);


	if (FAILED(GameDevice::instance().m_swapChain->Present(0, 0))) {
		//temporary exception..
		//will do some method here
		throw std::exception("Game::render() failed");
	}
}


void Game::run(UINT width, UINT height)
{
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	//init System
	
	GameWindow::instance().init(width, height);
	GameDevice::instance().init();
	GameTimer::instance().init();

	//user's init() - virtual func
	init();

	//LOOP
	MSG msg = {};

	while (1)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
			{
				break;
			}
		}

		Tick();

	}

	CoUninitialize();
}
