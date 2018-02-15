#include "pch.h"
#include "GameEffect.h"

#include "GameDevice.h"



#pragma region INPUT_DESCs


#pragma endregion

#pragma region IMPLEMENTATIONs

//LOAD BINARY
Effect::Effect(std::string effectName)
{
#ifdef _DEBUG
	ifstream file("./Content/shaders/" + effectName + ".cso", ios::binary | ios::ate | ios::in);
#else
	ifstream file("./Content/shaders/" + effectName + ".cso", ios::binary | ios::ate | ios::in);
#endif


	if (file.is_open())
	{
		UINT size = static_cast<UINT>( file.tellg() );
		vector<char> buffer(size);

		file.seekg(0, ios::beg);
		file.read(buffer.data(), size);
		file.close();

		HRESULT hr = D3DX11CreateEffectFromMemory(buffer.data(), size, 0, GameDevice::instance().m_device.Get(),
			m_effect.GetAddressOf());
	}
	else 
		throw std::exception("file read exception");
}


ColorEffect::ColorEffect(string effectName)
	:Effect(effectName)
{
	m_colorTech = m_effect->GetTechniqueByName("ColorTech");
	m_wvp = m_effect->GetVariableByName("gWorldViewProj")->AsMatrix();


	D3DX11_PASS_DESC passDesc;
	m_colorTech->GetPassByIndex(0)->GetDesc(&passDesc);
	GameDevice::instance().m_device->CreateInputLayout(InputLayoutDesc::PositionColor, 2, passDesc.pIAInputSignature,
		passDesc.IAInputSignatureSize, m_inputLayout.GetAddressOf());
}


ColorEffect::~ColorEffect()
{
}

#pragma endregion

#pragma region GLOBAL

GameEffect::GameEffect()
{
}

GameEffect::~GameEffect()
{
}

void GameEffect::init()
{
	colorEffect = make_shared<ColorEffect>("color");

}

#pragma endregion


