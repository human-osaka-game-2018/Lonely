/**
* @file Pasoken.cpp
* @brief Pasokenクラスのソースファイル
* @author shion-sagawa
*/

#include "Pasoken.h"
#include "../../../../GameLib/GameLib.h"
#include "../../../../GameLib/CollisionManager/CollisionBase/CollisionBox.h"

#define _CRT_SECURE_NO_WARNINGS

Pasoken::Pasoken()
	: m_pSharedInformation(SharedInformation::Instance.GetSharedInformation())
{
	Initialize();
}

Pasoken::~Pasoken()
{
	Finalize();
}

//初期化する
bool Pasoken::Initialize()
{
	m_fbxModel.Load("../Graphics/fbxModel/wanpaso_color.fbx");
	m_shpere.CreateShpere(32);
	m_position = { -50.f, 0.f, 50.f };
	m_followingPositionExceptY = m_position;
	m_prevPosition = m_position;
	m_destinationPosition = { 10.f, 0.f, 10.f };
	m_destination = DESTINATION1;
	m_radius = 0.5f;
	m_speed = 0.15f;
	m_direction = 2.1f;
	
	D3DXVECTOR3 length(6.f, 6.f, 6.f);
	m_pCollision = new CollisionBox(this, ENEMY, &length);
	return true;
}

//解放する
void Pasoken::Finalize()
{
	m_fbxModel.Finalize();
	m_shpere.Finalize();
	delete m_pCollision;
}

//更新する
void Pasoken::Update()
{

	//目的地への方向ベクトルを求める
	D3DXVECTOR3 vecDestinationDirection(
		m_destinationPosition.x - m_position.x,
		m_destinationPosition.y - m_position.y,
		m_destinationPosition.z - m_position.z);

	//ベクトルの大きさを保存する
	float vecSize;
	vecSize = powf(
		(vecDestinationDirection.x * vecDestinationDirection.x) +
		(vecDestinationDirection.z * vecDestinationDirection.z), 0.5);

	float distance;
	distance = powf(
		(vecDestinationDirection.x * vecDestinationDirection.x) +
		(vecDestinationDirection.y * vecDestinationDirection.y) +
		(vecDestinationDirection.z * vecDestinationDirection.z), 0.5);

	//目的地の近くに来たら、違う目的地へ変更する
	if (vecSize <= 2.0f)
	{
		if (m_destination == DESTINATION1)
		{
			m_destinationPosition = { 20.f, 0.f, 0.f };
			m_destination = DESTINATION2;
		}
		else if (m_destination == DESTINATION2)
		{
			m_destinationPosition = { 0.f, 0.f, 20.f };
			m_destination = DESTINATION3;
		}
		else if (m_destination == DESTINATION3)
		{
			m_destinationPosition = { -10.f,0.f,-10.f };
			m_destination = DESTINATION1;
		}
	}

	//単位ベクトルを出してから、スピードを掛けて、移動量を計算する
	D3DXVECTOR3 movementSpeed = { 0.f,0.f,0.f };
	movementSpeed.x = (vecDestinationDirection.x / vecSize) * m_speed;
	movementSpeed.z = (vecDestinationDirection.z / vecSize) * m_speed;

	//このフレームで移動する量
	D3DXVECTOR3 movementThisFrame = { 0.f,0.f,0.f };

	movementThisFrame.x += movementSpeed.x;
	movementThisFrame.z += movementSpeed.z;

	//当たり判定を登録する
	m_pCollisionManager->RegisterCollision(m_pCollision);

	////キー入力で移動
	//if (DIRECT_INPUT->KeyboardIsHeld(DIK_W))
	//{
	//	//移動量を保存
	//	movementThisFrame.x += movementSpeed.x;
	//	movementThisFrame.z += movementSpeed.z;

	//	//キャラの向きを変える
	//	m_direction = m_pSharedInformation->GetCameraDirection();

	//}
	//if (DIRECT_INPUT->KeyboardIsHeld(DIK_S))
	//{
	//	movementThisFrame.x -= movementSpeed.x;
	//	movementThisFrame.z -= movementSpeed.z;

	//	m_direction = m_pSharedInformation->GetCameraDirection() + 3.14;
	//}
	//if (DIRECT_INPUT->KeyboardIsHeld(DIK_A))
	//{
	//	movementThisFrame.x -= movementSpeed.z;
	//	movementThisFrame.z += movementSpeed.x;

	//	m_direction = m_pSharedInformation->GetCameraDirection() - 1.57;
	//}
	//if (DIRECT_INPUT->KeyboardIsHeld(DIK_D))
	//{
	//	movementThisFrame.x += movementSpeed.z;
	//	movementThisFrame.z -= movementSpeed.x;

	//	m_direction = m_pSharedInformation->GetCameraDirection() + 1.57;
	//}
	//if (DIRECT_INPUT->KeyboardIsHeld(DIK_F))
	//{
	//	movementThisFrame.y += movementSpeed.y;
	//}

	//移動させる前の位置を保存する
	m_prevPosition.x = m_position.x;
	m_prevPosition.y = m_position.y;
	m_prevPosition.z = m_position.z;
	m_followingPositionExceptY.y = m_position.y;
	
	//移動させる
	m_position.x += movementThisFrame.x;
	m_position.y += movementThisFrame.y;
	m_position.z += movementThisFrame.z;


	//壁との当たり判定をどうにかできないか検証
	//hitDist = 1.0;
	//D3DXVECTOR3 hitPos2(m_position);
	//D3DXVECTOR3 sabun;
	//hitPos2.y += 1.0f;
	//hitPos2.z += 0.0f;

	//// 地面との当たり判定(プレイヤーの位置から真下に当たり判定を行う)
	//if (m_pFbxStage.RayPick(&hitPos2, &D3DXVECTOR3(movementThisFrame.x, 0.0f, movementThisFrame.z), &hitDist, &hitPos2) != -1)//単位ベクトルじゃないと
	//{
	//	// 当たった場合はプレイヤーの位置を壁に設置させる
	//	sabun.x = (m_position.x - (hitPos2.x + m_radius));
	//	sabun.z = (m_position.z - (hitPos2.z + m_radius));
	//	movementThisFrame.x += sabun.x;
	//	movementThisFrame.z += sabun.z;

	//	m_position.x = hitPos2.x + m_radius;
	//	m_position.z = hitPos2.x + m_radius;
	//}

	//移動した分を保存する
	m_followingPositionExceptY.x = m_position.x;
	m_followingPositionExceptY.z = m_position.z;

	// モデルの行列を算出
	D3DXMATRIX rot, trans, scale;
	D3DXMatrixScaling(&scale, m_radius, m_radius, m_radius);
	D3DXMatrixRotationY(&rot,/* D3DXToRadian*/(m_direction));
	D3DXMatrixTranslation(&trans, m_position.x, m_position.y, m_position.z);
	D3DXMatrixMultiply(m_shpere.GetWorld(), &scale, &rot);
	D3DXMatrixMultiply(m_shpere.GetWorld(), m_shpere.GetWorld(), &trans);

	*m_fbxModel.GetWorld() = *m_shpere.GetWorld();

}

//描画する
void Pasoken::Render()
{
	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();
	DirectX* pDirectX = GameLib::Instance.GetDirectX();

	// 通常書き込みモードに設定
	pDirectX->SetRenderMode(DirectX::Normal, false);

	// Zテストの比較方法
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// モデルの描画
	m_fbxModel.Render();
	
	/*char s[50];
	sprintf_s(s,50,"position.x %f", m_position.x);
	DEBUGFONT->DrawText(50, 50, 0xffffffff, s);
	*/
}

void Pasoken::RevertPosition()
{
	m_position = m_prevPosition;
	m_followingPositionExceptY = m_prevPosition;
}
