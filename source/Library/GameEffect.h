#pragma once

#include "pch.h"


#pragma region IMPLEMENTAIONs

//EFFECTs
class Effect {
public:
	Effect(std::string effectName);


public:
	Microsoft::WRL::ComPtr< ID3DX11Effect> m_effect = nullptr;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout = nullptr;
};


class ColorEffect :public Effect
{
public:
	ColorEffect(string effectName);
	~ColorEffect();


public:
	ID3DX11EffectTechnique* m_colorTech = nullptr;
	ID3DX11EffectMatrixVariable* m_wvp = nullptr;

};

#pragma endregion





#pragma region GLOBAL

class GameEffect : public GameSingleton<GameEffect>{
public:
	GameEffect();
	~GameEffect();

	void init();
public:
	std::shared_ptr< ColorEffect> colorEffect;
};


#pragma endregion