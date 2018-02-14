#pragma once



// Use the C++ standard templated min/max
#define NOMINMAX

// DirectX apps don't need GDI
#define NODRAWTEXT
#define NOGDI
#define NOBITMAP


//추가 라이브러리 사용 알려주기
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
	throw가 실행되면 catch 를 만날때까지 호출 스택을 타고 올라가면서 동시에 메모리 해제를 진행한다.
	호출 스택에 있는 함수들을 하나하나 빠져나오면서 거기서 생성된 지역 변수들을 전부 해제한다.
	만약 지역 변수에 new를 이용한 메모리 할당을 한 변수가 있다면, 해제가 안된다.
	스마트 포인터로 할당했다면 지역 변수를 빠져나오면서 참조 카운트가 내려갈태니 정상적으로 
	힙 영역에서 해제가 된다. 
*/

/*
	# ComPtr operator& 
	operator& maps to ReleaseAndGetAddressOf()
*/