#pragma once

using namespace Microsoft::WRL;

class GameDevice
{
public:
	struct VideoCardInfo {
		VideoCardInfo() :
			videoCardName(""),memory(0)
		{

		}
		std::string videoCardName;
		UINT memory;
	};

	struct DisplayInfo {
		DisplayInfo():
			refreshRate(0), numerator(0), denominator(0)
		{  

		}
		UINT refreshRate;
		int numerator,denominator;
		
	};

public:
	GameDevice();
	~GameDevice();

	SINGLETON(GameDevice);
	
	void init();

private:
	void initAdapterInfo();
	void initD3D();
	void onResize();

public:
	ComPtr<ID3D11Device> m_device;
	ComPtr<ID3D11DeviceContext> m_context;


	ComPtr< IDXGISwapChain > m_swapChain;
	vector<DXGI_SAMPLE_DESC > m_arrSampleDesc;
	UINT m_defaultSampleCount = 4;

	ComPtr<ID3D11Texture2D> m_depthStencilBuffer;
	ComPtr<ID3D11DepthStencilView> m_depthStencilView;
	ComPtr<ID3D11RenderTargetView> m_renderTargetView;
	D3D11_VIEWPORT m_screenViewport;

	VideoCardInfo m_videoCardInfo;
	DisplayInfo m_displayInfo;

private:
	HWND m_hWnd;
};

