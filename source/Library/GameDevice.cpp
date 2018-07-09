#include "pch.h"
#include "GameDevice.h"
#include "GameWindow.h"

GameDevice::GameDevice():
	m_defaultSampleCount(4)
{
}


GameDevice::~GameDevice()
{
}

void GameDevice::init()
{
	m_hWnd = GameWindow::instance().m_hWnd;

	initAdapterInfo();
	initD3D();


	//GameWindow::instance().AddFuncToMsg(WM_SIZE, [&](WPARAM wParam, LPARAM lParam) {
		//this->onResize();
	//});
	
}


void GameDevice::initD3D()
{
	UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif



	D3D_FEATURE_LEVEL featureLevel;
	if (FAILED(D3D11CreateDevice(
		0,                 // default adapter
		D3D_DRIVER_TYPE_HARDWARE,
		0,                 // no software device
		createDeviceFlags,
		0, 0,              // default feature level array
		D3D11_SDK_VERSION,
		m_device.ReleaseAndGetAddressOf(),
		&featureLevel,
		m_context.ReleaseAndGetAddressOf()))) 
	{
		throw std::exception("create device failed");
	}



	if (featureLevel != D3D_FEATURE_LEVEL_11_0)
	{
		throw std::exception("directx 11 unsupported computer");
	}

	for (UINT sampleCount = 1; sampleCount <= D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT; ++sampleCount) {
		UINT quality = 0;

		m_device->CheckMultisampleQualityLevels(
			DXGI_FORMAT_R8G8B8A8_UNORM, sampleCount, &quality);

		if (quality > 0)
		{
			DXGI_SAMPLE_DESC desc = { sampleCount,quality - 1 };
			m_arrSampleDesc.push_back(desc);

		}
	}

	RECT rc = {};
	GetClientRect(m_hWnd, &rc);

	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width = rc.right;
	sd.BufferDesc.Height = rc.bottom;
	sd.BufferDesc.RefreshRate.Numerator = m_displayInfo.numerator;
	sd.BufferDesc.RefreshRate.Denominator = m_displayInfo.denominator;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	//Use MSAA
	if (m_arrSampleDesc.size() > 0)
	{
		DXGI_SAMPLE_DESC desc = getHighestSampleCountDesc();

		sd.SampleDesc.Count = desc.Count;
		sd.SampleDesc.Quality = desc.Quality;
	}
	//No MSAA
	else
	{
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
	}

	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = m_hWnd;
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	ComPtr< IDXGIDevice>dxgiDevice = 0;
	m_device.As(&dxgiDevice);

	ComPtr< IDXGIAdapter> dxgiAdapter = 0;
	dxgiDevice->GetAdapter(&dxgiAdapter);


	ComPtr< IDXGIFactory> dxgiFactory = 0;
	dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)dxgiFactory.GetAddressOf());


	if (FAILED(dxgiFactory->CreateSwapChain(m_device.Get(), &sd, m_swapChain.ReleaseAndGetAddressOf())))
	{
		throw std::exception("create swapchain failed");
	}

	onResize(rc.right,rc.bottom);
}

void GameDevice::onResize(UINT width, UINT height)
{
	// Release the old views, as they hold references to the buffers we
	// will be destroying.  Also release the old depth/stencil buffer.
	m_renderTargetView.Reset();
	m_depthStencilView.Reset();
	m_depthStencilBuffer.Reset();

	// Resize the swap chain and recreate the render target view.
	m_swapChain->ResizeBuffers(1, width,height, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
	ComPtr <ID3D11Texture2D> backBuffer;
	m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf()));
	m_device->CreateRenderTargetView(backBuffer.Get(), 0, m_renderTargetView.GetAddressOf());

	// Create the depth/stencil buffer and view.
	D3D11_TEXTURE2D_DESC depthStencilDesc;

	depthStencilDesc.Width = width;
	depthStencilDesc.Height = height;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	//Use MSAA
	if (m_arrSampleDesc.size() > 0)
	{
		DXGI_SAMPLE_DESC desc = getHighestSampleCountDesc();

		depthStencilDesc.SampleDesc.Count = desc.Count;
		depthStencilDesc.SampleDesc.Quality = desc.Quality;
	}
	//No MSAA
	else
	{
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
	}

	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	m_device->CreateTexture2D(&depthStencilDesc, 0, m_depthStencilBuffer.ReleaseAndGetAddressOf());
	if (FAILED(m_device->CreateDepthStencilView(m_depthStencilBuffer.Get(), 0, m_depthStencilView.ReleaseAndGetAddressOf())))
	{
		throw std::exception("create depth stencil view failed");
	}
	

	// Bind the render target view and depth/stencil view to the pipeline.

	m_context->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());


	// Set the viewport transform.

	m_screenViewport.TopLeftX = 0;
	m_screenViewport.TopLeftY = 0;
	m_screenViewport.Width = static_cast<float>(width);
	m_screenViewport.Height = static_cast<float>(height);
	m_screenViewport.MinDepth = 0.0f;
	m_screenViewport.MaxDepth = 1.0f;

	m_context->RSSetViewports(1, &m_screenViewport);

	cout << "onResize() called" << endl;
}

DXGI_SAMPLE_DESC GameDevice::getHighestSampleCountDesc()
{
	return m_arrSampleDesc.back();
}

DXGI_SAMPLE_DESC GameDevice::getSampleCountDesc(UINT count)
{
	DXGI_SAMPLE_DESC desc;
	UINT idx;

	for (idx = 0; idx< m_arrSampleDesc.size(); ++idx) {
		if (m_arrSampleDesc[idx].Count == count)
		{
			break;
		}
	}

	desc.Count = m_arrSampleDesc[idx].Count;
	desc.Quality = m_arrSampleDesc[idx].Quality;

	return desc;
}

void GameDevice::initAdapterInfo()
{
	ComPtr< IDXGIFactory> factory;
	ComPtr<IDXGIAdapter> adapter;
	ComPtr<IDXGIOutput> adapterOutput;
	DXGI_ADAPTER_DESC adapterDesc;
	std::vector<DXGI_MODE_DESC> displayModeList;
	CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(factory.GetAddressOf()));
	UINT numModes;

	// Use the factory to create an adapter for the primary graphics interface (video card).
	factory->EnumAdapters(0, adapter.GetAddressOf());


	// Enumerate the primary adapter output (monitor).
	adapter->EnumOutputs(0, adapterOutput.GetAddressOf());


	// Get the number of modes that fit the DXGI_FORMAT_R8G8B8A8_UNORM display format for the adapter output (monitor).
	adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);


	// Create a list to hold all the possible display modes for this monitor/video card combination.

	// Now fill the display mode list structures.
	displayModeList.resize(numModes);
	adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList.data());


	// Now go through all the display modes and find the one that matches the screen width and height.
	// When a match is found store the numerator and denominator of the refresh rate for that monitor.

	UINT width = GetSystemMetrics(SM_CXSCREEN);
	UINT height = GetSystemMetrics(SM_CYSCREEN);
	for (UINT i = 0; i < numModes; i++)
	{
		if (displayModeList[i].Width == width)
		{
			if (displayModeList[i].Height == height)
			{
				m_displayInfo.numerator = displayModeList[i].RefreshRate.Numerator / 1000;
				m_displayInfo.denominator = displayModeList[i].RefreshRate.Denominator / 1000;
				break;
			}
		}
	}

	// Get the adapter (video card) description.
	adapter->GetDesc(&adapterDesc);

	// Store the dedicated video card memory in megabytes.
	m_videoCardInfo.memory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

	// Convert the name of the video card to a character array and store it.
	wstring ws(adapterDesc.Description);
	m_videoCardInfo.videoCardName = string(ws.begin(), ws.end());

}

