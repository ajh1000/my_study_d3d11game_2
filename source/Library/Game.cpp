#include "pch.h"
#include "Game.h"

#include "GameWindow.h"
#include "GameDevice.h"
#include "GameTimer.h"
#include "GameEffect.h"
#include "GameScene.h"
#include "GameInput.h"


Game::Game()
{
}


Game::~Game()
{

}


void Game::addScene(const char* sceneName, shared_ptr<GameScene> scene)
{
	scene->init();
	m_mapScene[sceneName] = scene;
}

void Game::setScene(shared_ptr<GameScene> scene)
{
	m_scene = scene;
}

void Game::setScene(const char * sceneName)
{
	m_scene = m_mapScene[sceneName];
}

void Game::Tick()
{
	GameTimer::instance().Tick([&]() {
		update();
		render();

	});

}

void Game::update()
{
	GameInput::instance().update();


	m_scene->update();

}

void Game::render()
{
	GameDevice::instance().m_context->ClearRenderTargetView(GameDevice::instance().m_renderTargetView.Get(),
		DirectX::Colors::Aquamarine);
	GameDevice::instance().m_context->ClearDepthStencilView(GameDevice::instance().m_depthStencilView.Get(),
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	m_scene->render();

	if (FAILED(GameDevice::instance().m_swapChain->Present(0, 0))) {
		//temporary exception..
		//will do some method here
		throw std::exception("Game::render() failed");
	}
}


void Game::run(unsigned int width, unsigned int height)
{
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	//init System
	GameWindow::instance().init(width, height);
	GameDevice::instance().init();
	GameTimer::instance().init();
	GameEffect::instance().init();
	GameInput::instance().init();


	
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