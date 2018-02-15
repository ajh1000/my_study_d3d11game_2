#pragma once

#include "pch.h"

//INPUT LAYOUT DESCs
class InputLayoutDesc {
public:
	static const D3D11_INPUT_ELEMENT_DESC Position[2];
	static const D3D11_INPUT_ELEMENT_DESC PositionColor[2];
	static const D3D11_INPUT_ELEMENT_DESC PositionTex[2];
	static const D3D11_INPUT_ELEMENT_DESC PositionTexNormal[3];
	static const D3D11_INPUT_ELEMENT_DESC PositionTexNormalTan[4];
	static const D3D11_INPUT_ELEMENT_DESC PosTexNormalSkinned[5];
	static const D3D11_INPUT_ELEMENT_DESC PosTexNormalTanSkinned[6];

};


//VERTICES
struct VertexPositionColor {
	SimpleMath::Vector3 pos;
	SimpleMath::Vector4 color;
};


