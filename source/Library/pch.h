#pragma once



// Use the C++ standard templated min/max
#define NOMINMAX

// DirectX apps don't need GDI
#define NODRAWTEXT
#define NOGDI
#define NOBITMAP


//C++  -  STANDARD
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


//D3D11  -  STANDARD
#include <d3d11.h>
#include <dxgi.h>
#include <DirectXColors.h>
#include <wrl/client.h>
using namespace Microsoft::WRL;


//EXTERNAL
#include "../../external/effects11/inc/d3dx11effect.h"
#include "../../external/directxtex/inc/DirectXTex.h"
#include "../../external/directxtk/inc/SimpleMath.h"
using namespace DirectX;
using namespace DirectX::SimpleMath;


//MISC
#include "GameVertexDef.h"
#include "GameSingleton.h"



//추가 라이브러리 사용 알려주기
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"dxgi.lib")

#ifdef _DEBUG
#pragma comment(lib,"..\\..\\external\\effects11\\lib\\for_debug\\Effects11d.lib")
#pragma comment(lib,"..\\..\\external\\directxtk\\lib\\for_debug\\DirectXTK.lib")
#pragma comment(lib,"..\\..\\external\\directxtex\\lib\\for_debug\\DirectXTex.lib")
#else
#pragma comment(lib,"..\\..\\external\\effects11\\lib\\for_release\\Effects11.lib")
#pragma comment(lib,"..\\..\\external\\directxtk\\lib\\for_release\\DirectXTK.lib")
#pragma comment(lib,"..\\..\\external\\directxtex\\lib\\for_release\\DirectXTex.lib")
#endif



/*
	#stack unwind
	throw가 실행되면 catch 를 만날때까지 호출 스택을 타고 올라가면서 동시에 메모리 해제를 진행한다.
	호출 스택에 있는 함수들을 하나하나 빠져나오면서 거기서 생성된 지역 변수들을 전부 해제한다.
	만약 지역 변수에 new를 이용한 메모리 할당을 한 변수가 있다면, 해제가 안된다.
	스마트 포인터로 할당했다면 지역 변수를 빠져나오면서 참조 카운트가 내려갈태니 정상적으로 
	힙 영역에서 해제가 된다. 


	# ComPtr operator& 
	operator& maps to ReleaseAndGetAddressOf()

	# LH & RH
	왼손 좌표계를 기준으로 만들어진 오브젝트들을 오른손 좌표계에 사용하고싶다면,
	z축 값에 -1을 곱한다. 그리고 왼손 좌표계에서 오브젝트를 바라봤을때의 장면과
	똑같은 장면을 오른손 좌표계에서도 보고싶다면 view 행렬의 eye의 포지션을 z축 반전시켜줘한다.

	#effects11 state Groups
	https://msdn.microsoft.com/en-us/library/windows/desktop/bb205052(v=vs.85).aspx
	https://msdn.microsoft.com/en-us/library/windows/desktop/bb205053(v=vs.85).aspx
*/