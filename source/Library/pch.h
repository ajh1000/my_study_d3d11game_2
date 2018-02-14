#pragma once



// Use the C++ standard templated min/max
#define NOMINMAX

// DirectX apps don't need GDI
#define NODRAWTEXT
#define NOGDI
#define NOBITMAP


//�߰� ���̺귯�� ��� �˷��ֱ�
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"dxgi.lib")

#ifdef _DEBUG
#pragma comment(lib,"..\\..\\external\\effects11\\lib\\for_debug\\Effects11d.lib")
#else
#pragma comment(lib,"..\\..\\external\\effects11\\lib\\for_release\\Effects11.lib")
#endif

//STANDARD 
#include <windows.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <vector>
#include <memory>
#include <functional>
#include <chrono>
using namespace std;



//D3D11 
#include <d3d11.h>
#include <dxgi.h>
#include <DirectXColors.h>
#include <wrl/client.h>


//DIRECTX TK
/*
#include <SimpleMath.h>
#include <DirectXTex.h>
using namespace DirectX;
using namespace DirectX::SimpleMath;
*/

/*
	#stack unwind
	throw�� ����Ǹ� catch �� ���������� ȣ�� ������ Ÿ�� �ö󰡸鼭 ���ÿ� �޸� ������ �����Ѵ�.
	ȣ�� ���ÿ� �ִ� �Լ����� �ϳ��ϳ� ���������鼭 �ű⼭ ������ ���� �������� ���� �����Ѵ�.
	���� ���� ������ new�� �̿��� �޸� �Ҵ��� �� ������ �ִٸ�, ������ �ȵȴ�.
	����Ʈ �����ͷ� �Ҵ��ߴٸ� ���� ������ ���������鼭 ���� ī��Ʈ�� �������´� ���������� 
	�� �������� ������ �ȴ�. 
*/

/*
	# ComPtr operator& 
	operator& maps to ReleaseAndGetAddressOf()
*/