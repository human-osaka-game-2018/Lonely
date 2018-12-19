/**
* @file TestCamera.cpp
* @brief TestCameraクラスのソースファイル
* @author shion-sagawa
*/

#include "TestCamera.h"
#include "../../../../GameLib/GameLib.h"


TestCamera::TestCamera()
	: m_pSharedInformation(SharedInformation::Instance.GetSharedInformation())
{
}

TestCamera::~TestCamera()
{
}

//初期化する
void TestCamera::Initialize()
{
	m_position = { 0.f,10.f,-10.f };
	m_lookAt = { 0.0f,0.f,0.f };
	m_rotation = { 0.f,0.f,0.f };
	m_perspective = D3DX_PI / 4;
}

//解放する
void TestCamera::Finalize()
{

}

//更新する
void TestCamera::Update()
{

	/*if (DIRECT_INPUT->KeyboardIsHeld(DIK_DOWN))
	{
		m_position.z -= 0.5f;
		m_lookAt.z -= 0.5f;
	}
	if (DIRECT_INPUT->KeyboardIsHeld(DIK_UP))
	{
		m_position.z += 0.5f;
		m_lookAt.z += 0.5f;
	}
	if (DIRECT_INPUT->KeyboardIsHeld(DIK_LEFT))
	{
		m_position.x -= 0.5f;
		m_lookAt.x -= 0.5f;
	}
	if (DIRECT_INPUT->KeyboardIsHeld(DIK_RIGHT))
	{
		m_position.x += 0.5f;
		m_lookAt.x += 0.5f;
	}
	if (DIRECT_INPUT->KeyboardIsHeld(DIK_T))
	{
		m_position.y += 0.5f;
		m_lookAt.y += 0.5f;
	}
	if (DIRECT_INPUT->KeyboardIsHeld(DIK_Y))
	{
		m_position.y -= 0.5f;
		m_lookAt.y -= 0.5f;
	}*/

	const float cameraRotationSpeed = 0.05f;
	if (DIRECT_INPUT->KeyboardIsHeld(DIK_DOWN))
	{
		m_rotation.x += cameraRotationSpeed;
		if (m_rotation.x >= 0.4f)
		{
			m_rotation.x = 0.4f;
		}
	}
	if (DIRECT_INPUT->KeyboardIsHeld(DIK_UP))
	{
		m_rotation.x -= cameraRotationSpeed;
		if (m_rotation.x <= -0.7f)
		{
			m_rotation.x = -0.7f;
		}
	}
	if (DIRECT_INPUT->KeyboardIsHeld(DIK_LEFT))
	{

		m_rotation.y -= cameraRotationSpeed;
	}
	if (DIRECT_INPUT->KeyboardIsHeld(DIK_RIGHT))
	{

		m_rotation.y += cameraRotationSpeed;
	}

	//カメラをプレイヤーが移動した分だけ移動させる
	D3DXVECTOR3 movement = m_pSharedInformation->GetPlayerMovement();
	m_position.x += movement.x;
	m_position.y += movement.y;
	m_position.z += movement.z;
	m_lookAt.x += movement.x;
	m_lookAt.y += movement.y;
	m_lookAt.z += movement.z;

	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();
	DirectX* pDirectX = GameLib::Instance.GetDirectX();

	////ワールドトランスフォーム（絶対座標変換）
	D3DXMATRIXA16 matWorld, matMovement;

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matMovement);
	D3DXMatrixMultiply(&matWorld, &matWorld, &matMovement);

	pDevice->SetTransform(D3DTS_WORLD, &matWorld);


	//// ビュートランスフォーム（視点座標変換）
	//D3DXVECTOR3 vecEyePt(m_position.x, m_position.y, m_position.z);  //カメラ（視点）位置
	D3DXVECTOR3 vecEyePt(0.f, 10.f, -10.f);                            //カメラ（視点）位置
	D3DXVECTOR3 vecLookatPt(m_lookAt.x, m_lookAt.y, m_lookAt.z);       //注視位置
	D3DXVECTOR3 vecUpVec(0.0f, 1.0f, 0.0f);                            //上方位置

	D3DXMATRIXA16 matView;                                             //ビュー行列
	D3DXMATRIXA16 matRotationX, matRotationY;                          //回転行列

	//カメラ位置を回転させる
	D3DXMatrixRotationX(&matRotationX, m_rotation.x);
	D3DXMatrixRotationY(&matRotationY, m_rotation.y);
	D3DXVec3TransformCoord(&vecEyePt, &vecEyePt, &matRotationX); 
	D3DXVec3TransformCoord(&vecEyePt, &vecEyePt, &matRotationY); 

	//回転させたカメラを原点にずらした分だけ戻す
	vecEyePt.x += m_position.x + 0.f;
	vecEyePt.y += m_position.y - 10.f;
	vecEyePt.z += m_position.z + 10.f;

	//回転させた後のカメラの位置を共有クラスに保存する
	m_pSharedInformation->SetCameraPosition(vecEyePt);
	//回転角度を共有クラスに保存する
	m_pSharedInformation->SetCameraDirection(m_rotation.y);

	D3DXMatrixLookAtLH(&matView, &vecEyePt, &vecLookatPt, &vecUpVec);
	pDevice->SetTransform(D3DTS_VIEW, &matView);


	//// プロジェクショントランスフォーム（射影変換）
	D3DXMatrixPerspectiveFovLH(&m_matProjection, m_perspective, 1.0f, 1.0f, 1000.0f);
	pDevice->SetTransform(D3DTS_PROJECTION, &m_matProjection);


	// ライトをあてる 白色で鏡面反射ありに設定
	D3DXVECTOR3 vecDirection(0, 0, 1);
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	light.Specular.r = 1.0f;
	light.Specular.g = 1.0f;
	light.Specular.b = 1.0f;
	light.Ambient.a = 1.0f;
	light.Ambient.r = 0.5f;
	light.Ambient.g = 0.5f;
	light.Ambient.b = 0.5f;
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDirection);
	light.Range = 200.0f;

	pDevice->SetLight(0, &light);
	pDevice->LightEnable(0, TRUE);

}
