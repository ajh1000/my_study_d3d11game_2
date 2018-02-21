#pragma once

#include "GameDevice.h"
#include "GameTimer.h"
#include "GameInput.h"

using namespace SimpleMath;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void init()=0;
	virtual void update() = 0;
	virtual void render();
protected:
	void createStaticVertexBuffer(void *pData, UINT sizeOfArr);
	void createDynamicVertexBuffer(void *pData, UINT sizeOfArr);
	void createIndexBuffer(void *pData, UINT sizeOfArr);

protected:
	ComPtr< ID3D11Buffer> m_vertexBuffer;
	bool m_isDynamicVertex=false;
	ComPtr< ID3D11Buffer> m_indexBuffer;

	Matrix view, proj;
};
