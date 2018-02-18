
#include "GameTriangle.h"



GameTriangle::GameTriangle()
{
}


GameTriangle::~GameTriangle()
{
}

void GameTriangle::init()
{ 
	/*

	VertexPositionColor vertices[3] = {
		Vector3(-1,-1,0),Vector4( DirectX::Colors::Red),
		Vector3(1,-1,0),Vector4(DirectX::Colors::Black),
		Vector3(0,1,0),Vector4(DirectX::Colors::Blue)

	};

	createStaticVertexBuffer(vertices, sizeof(vertices));

	UINT indices[] = {
		0,2,1
	};
	createIndexBuffer(indices, sizeof(indices));
	*/



	//VB
	VertexPositionColor vertices[] =
	{
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), Colors::White },
		{ XMFLOAT3(-1.0f, +1.0f, -1.0f), Colors::Black },
		{ XMFLOAT3(+1.0f, +1.0f, -1.0f), Colors::Red },
		{ XMFLOAT3(+1.0f, -1.0f, -1.0f), Colors::Green },
		{ XMFLOAT3(-1.0f, -1.0f, +1.0f), Colors::Blue },
		{ XMFLOAT3(-1.0f, +1.0f, +1.0f), Colors::Yellow },
		{ XMFLOAT3(+1.0f, +1.0f, +1.0f), Colors::Cyan },
		{ XMFLOAT3(+1.0f, -1.0f, +1.0f), Colors::Magenta }
	};

	//flip-z for right-handed
	for (auto& o : vertices) {
		o.pos.z *= -1;
	}

	createStaticVertexBuffer(vertices, sizeof(vertices));
	//IB
	UINT indices[] = {
		// front face
		0, 1, 2,
		0, 2, 3,

		// back face
		4, 6, 5,
		4, 7, 6,

		// left face
		4, 5, 1,
		4, 1, 0,

		// right face
		3, 2, 6,
		3, 6, 7,

		// top face
		1, 5, 6,
		1, 6, 2,

		// bottom face
		4, 0, 3,
		4, 3, 7
	};

	createIndexBuffer(indices, sizeof(indices));
}

void GameTriangle::update()
{
}
