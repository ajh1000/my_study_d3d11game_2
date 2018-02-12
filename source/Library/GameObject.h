#pragma once

class GameTimer;
class GameModelImporter;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	void init(ID3D11Device* device, ID3D11DeviceContext* context);

protected:
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_context;

};


/*
	device
	context
	timer
	inputDesc,effects
	model import
*/