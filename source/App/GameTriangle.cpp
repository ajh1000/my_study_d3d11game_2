
#include "GameTriangle.h"



GameTriangle::GameTriangle()
{
}


GameTriangle::~GameTriangle()
{
}

void GameTriangle::init()
{ 

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
	/*
	if (GameInput::instance().isKeyPressed(KeyCode::W)) {
		cout << "W pressed" << endl;
	}
	if (GameInput::instance().isKeyPressed(KeyCode::E)) {
		cout << "S pressed" << endl;
	}

	if (GameInput::instance().isKeyHeld(KeyCode::W)) {
		cout << "W held" << endl;
	}
	if (GameInput::instance().isKeyHeld(KeyCode::E)) {
		cout << "S held" << endl;
	}


	if (GameInput::instance().isKeyReleased(KeyCode::W)) {
		cout << "W Released" << endl;
	}
	if (GameInput::instance().isKeyReleased(KeyCode::E)) {
		cout << "S Released" << endl;
	}

	if (GameInput::instance().isKeyPressed(KeyCode::LBUTTON)) {
		cout << "LBUTTON pressed" << endl;
	}
	if (GameInput::instance().isKeyPressed(KeyCode::RBUTTON)) {
		cout << "RBUTTON pressed" << endl;
	}

	if (GameInput::instance().isKeyHeld(KeyCode::LBUTTON)) {
		cout << "LBUTTON held" << endl;
	}
	if (GameInput::instance().isKeyHeld(KeyCode::RBUTTON)) {
		cout << "RBUTTON held" << endl;
	}


	if (GameInput::instance().isKeyReleased(KeyCode::LBUTTON)) {
		cout << "LBUTTON Released" << endl;
	}
	if (GameInput::instance().isKeyReleased(KeyCode::RBUTTON)) {
		cout << "RBUTTON Released" << endl;
	}
	*/

	if (GameInput::instance().isKeyPressed(KeyCode::X1BUTTON)) {
		cout << "X1BUTTON pressed" << endl;
	}
	if (GameInput::instance().isKeyPressed(KeyCode::X2BUTTON)) {
		cout << "X2BUTTON pressed" << endl;
	}

	if (GameInput::instance().isKeyHeld(KeyCode::X1BUTTON)) {
		cout << "X1BUTTON held" << endl;
	}
	if (GameInput::instance().isKeyHeld(KeyCode::X2BUTTON)) {
		cout << "X2BUTTON held" << endl;
	}


	if (GameInput::instance().isKeyReleased(KeyCode::X1BUTTON)) {
		cout << "X1BUTTON Released" << endl;
	}
	if (GameInput::instance().isKeyReleased(KeyCode::X2BUTTON)) {
		cout << "X2BUTTON Released" << endl;
	}
}
