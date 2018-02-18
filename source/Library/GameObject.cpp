#include "pch.h"
#include "GameObject.h"
#include "GameEffect.h"
#include "GameWindow.h"
#include "GameDevice.h"

GameObject::GameObject()
	:m_isDynamicVertex(false)
{
	/*
	view = XMMatrixLookAtLH(Vector3(0, 0, -7.f),
		Vector3::Zero, Vector3::UnitY);
	proj = XMMatrixPerspectiveFovLH(XM_PI / 4.f,
		float(GameDevice::instance().m_screenViewport.Width) / 
		float(GameDevice::instance().m_screenViewport.Height), 0.1f, 1000.f);
	*/
	view = Matrix::CreateLookAt(Vector3(0, 0, 7.f),
		Vector3::Zero, Vector3(0,1,0));
	proj = Matrix::CreatePerspectiveFieldOfView(XM_PI / 4.f,
		float(GameDevice::instance().m_screenViewport.Width) /
		float(GameDevice::instance().m_screenViewport.Height), 0.1f, 1000.f);
	
}


GameObject::~GameObject()
{
}

void GameObject::render()
{
	Matrix world;
	Matrix wvp = world*view*proj;
	wvp.Transpose();

	GameDevice::instance().m_context->IASetInputLayout(GameEffect::instance().colorEffect->m_inputLayout.Get());
	GameDevice::instance().m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	UINT stride = sizeof(VertexPositionColor);
	UINT offset = 0;
	GameDevice::instance().m_context->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);
	GameDevice::instance().m_context->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);


	GameEffect::instance().colorEffect->m_wvp->SetMatrix(reinterpret_cast<const float*>(wvp.m));

	D3DX11_TECHNIQUE_DESC techDesc;
	GameEffect::instance().colorEffect->m_colorTech->GetDesc(&techDesc);
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		GameEffect::instance().colorEffect->m_colorTech->GetPassByIndex(p)->Apply(0, 
			GameDevice::instance().m_context.Get());


		GameDevice::instance().m_context->DrawIndexed(36, 0, 0);
	}

}

void GameObject::createStaticVertexBuffer(void * pData, UINT sizeOfArr)
{
	D3D11_BUFFER_DESC desc;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeOfArr;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = pData;

	GameDevice::instance().m_device->CreateBuffer(&desc, &initData, m_vertexBuffer.GetAddressOf());

}

void GameObject::createDynamicVertexBuffer(void * pData, UINT sizeOfArr)
{
	D3D11_BUFFER_DESC desc;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.ByteWidth = sizeOfArr;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags =D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = pData;

	GameDevice::instance().m_device->CreateBuffer(&desc, &initData, m_vertexBuffer.GetAddressOf());

	m_isDynamicVertex = true;

}

void GameObject::createIndexBuffer(void * pData, UINT sizeOfArr)
{
	D3D11_BUFFER_DESC desc;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeOfArr;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = pData;

	GameDevice::instance().m_device->CreateBuffer(&desc, &initData, m_indexBuffer.GetAddressOf());

}
