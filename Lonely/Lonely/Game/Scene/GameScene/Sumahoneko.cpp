/**
* @file Sumahoneko.cpp
* @brief Sumahonekoクラスのソースファイル
* @author shion-sagawa
*/

#include "Sumahoneko.h"
#include "../../../GameLib/GameLib.h"

#define _CRT_SECURE_NO_WARNINGS

Sumahoneko::Sumahoneko()
	: m_pSharedInformation(SharedInformation::Instance.GetSharedInformation())
{
	Initialize();
}

Sumahoneko::~Sumahoneko()
{
	Finalize();
}

//初期化する
bool Sumahoneko::Initialize()
{
	m_fbxStage.Load("../Graphics/stage2_1.fbx");
	m_fbxModel.Load("../Graphics/sumahoneko.fbx");
	m_shpere.CreateShpere(32);

	m_position = { 0.f, 0.f, 0.f };
	m_playerRadius = 0.1f;
	m_playerSpeed = 0.1f;
	m_playerDirection = 0.0f;
	return true;
}

//解放する
void Sumahoneko::Finalize()
{
	m_fbxModel.Finalize();
	m_fbxStage.Finalize();
	m_shpere.Finalize();
}

//更新する
void Sumahoneko::Update()
{
	//スピードを決める
	float transSpeed = 0.1f;

	//カメラの位置を取得する
	D3DXVECTOR3 cameraPosition = m_pSharedInformation->GetCameraPosition();
	//カメラの方向ベクトルを求める
	D3DXVECTOR3 vecCameraDirection(m_position.x - cameraPosition.x, m_position.y -cameraPosition.y, m_position.z - cameraPosition.z);

	//ベクトルの大きさを保存する
	float vecSize;
	vecSize = powf((vecCameraDirection.x * vecCameraDirection.x) + (vecCameraDirection.y * vecCameraDirection.y) + (vecCameraDirection.z*vecCameraDirection.z), 0.5);

	//単位ベクトルを出してから、スピードを掛けて、移動量を計算する
	D3DXVECTOR3 movementSpeed = {0.f,0.f,0.f};
	movementSpeed.x = (vecCameraDirection.x / vecSize) * transSpeed;
	movementSpeed.z = (vecCameraDirection.z / vecSize) * transSpeed;

	//このフレームで移動する量
	D3DXVECTOR3 movementThisFrame = { 0.f,0.f,0.f };
	
	//キー入力で移動
	if (DIRECT_INPUT->KeyboardIsHeld(DIK_W))
	{
		//移動量を保存
		movementThisFrame.x += movementSpeed.x;
		movementThisFrame.z += movementSpeed.z;
		
		//キャラの向きを変える
		m_playerDirection = m_pSharedInformation->GetCameraDirection();

	}
	if (DIRECT_INPUT->KeyboardIsHeld(DIK_S))
	{
		movementThisFrame.x -= movementSpeed.x;
		movementThisFrame.z -= movementSpeed.z;
		
		m_playerDirection = m_pSharedInformation->GetCameraDirection() + 3.14;
	}
	if (DIRECT_INPUT->KeyboardIsHeld(DIK_A))
	{
		movementThisFrame.x -= movementSpeed.z;
		movementThisFrame.z += movementSpeed.x;
		
		m_playerDirection = m_pSharedInformation->GetCameraDirection() - 1.57;
	}
	if (DIRECT_INPUT->KeyboardIsHeld(DIK_D))
	{
		movementThisFrame.x += movementSpeed.z;
		movementThisFrame.z -= movementSpeed.x;
		
		m_playerDirection = m_pSharedInformation->GetCameraDirection() + 1.57;
	}
	if (DIRECT_INPUT->KeyboardIsHeld(DIK_F))
	{
		movementThisFrame.y += movementSpeed.y;
	}

	//スマホ猫を移動させる
	m_position.x += movementThisFrame.x;
	m_position.y += movementThisFrame.y;
	m_position.z += movementThisFrame.z;

	//多分hitDistはレイの距離の制限
	float hitDist = 3.0f;
	D3DXVECTOR3 hitPos(m_position);
	// 足元基準に当たり判定をとる場合は少し上から判定する
	m_position.y += 1.0f;
	hitPos.y += 1.0f;
	const float tyousei = 0.5f;
	// 地面との当たり判定(プレイヤーの位置から真下に当たり判定を行う)
	if (m_fbxStage.RayPick(&m_position, &D3DXVECTOR3(0.0f, -1.0f, 0.0f), &hitDist, &hitPos) != -1)
	{
		// 当たった場合はプレイヤーの高さを地面に設置させる
		m_position.y = hitPos.y + m_playerRadius;
	}
	else
	{
		m_position.y -= 1.0f;
	}


	{
		//多分hitDistはレイの距離の制限
		float hitDist2 = fabs(movementThisFrame.x);
		D3DXVECTOR3 hitPos2(m_position);
		// 足元基準に当たり判定をとる場合は少し上から判定する
		m_position.y += 2.0f;
		hitPos2.y += 2.0f;
		// 地面との当たり判定(プレイヤーの位置から真下に当たり判定を行う)
		if (m_fbxStage.RayPick(&m_position, &D3DXVECTOR3(movementThisFrame.x, 0.0f, 0.0f), &hitDist2, &hitPos2) != -1)
		{
			if (movementThisFrame.x > 0) 
			{
				//当たり判定でずれた分だけ保存する
				movementThisFrame.x += (hitPos2.x - tyousei) - m_position.x;
				// 当たった場合はプレイヤーの高さを地面に設置させる
				m_position.x = hitPos2.x - tyousei;
			}
			else if (movementThisFrame.x <= 0)
			{
				//当たり判定でずれた分だけ保存する
				movementThisFrame.x += (hitPos2.x + tyousei) - m_position.x;
				m_position.x = hitPos2.x + tyousei;
			}
			m_position.y -= 2.0f;
		}
		else
		{
			m_position.y -= 2.0f;
		}
	}
	{
		float hitDist2 = fabs(movementThisFrame.x);
		D3DXVECTOR3 hitPos2(m_position);
		// 足元基準に当たり判定をとる場合は少し上から判定する
		m_position.y += 0.5f;
		hitPos2.y += 0.5f;
		// 地面との当たり判定(プレイヤーの位置から真下に当たり判定を行う)
		if (m_fbxStage.RayPick(&m_position, &D3DXVECTOR3(movementThisFrame.x, 0.0f, 0.0f), &hitDist2, &hitPos2) != -1)
		{
			if (movementThisFrame.x > 0) 
			{
				//当たり判定でずれた分だけ保存する
				movementThisFrame.x += (hitPos2.x - tyousei) - m_position.x;
				// 当たった場合はプレイヤーの高さを地面に設置させる
				m_position.x = hitPos2.x - tyousei;
			}
			else if (movementThisFrame.x <= 0)
			{
				//当たり判定でずれた分だけ保存する
				movementThisFrame.x += (hitPos2.x + tyousei) - m_position.x;
				m_position.x = hitPos2.x + tyousei;
			}
			m_position.y -= 0.5f;
		}
		else
		{
			m_position.y -= 0.5f;
		}
	}

	{
		//多分hitDistはレイの距離の制限
		float hitDist2 = fabs(movementThisFrame.z);
		D3DXVECTOR3 hitPos2(m_position);
		// 足元基準に当たり判定をとる場合は少し上から判定する
		m_position.y += 2.0f;
		hitPos2.y += 2.0f;
		// 地面との当たり判定(プレイヤーの位置から真下に当たり判定を行う)
		if (m_fbxStage.RayPick(&m_position, &D3DXVECTOR3(0.f, 0.0f, movementThisFrame.z), &hitDist2, &hitPos2) != -1)
		{
			if (movementThisFrame.z > 0) {
				//当たり判定でずれた分だけ保存する
				movementThisFrame.z +=(hitPos2.z - tyousei) -  m_position.z;
				// 当たった場合はプレイヤーの高さを地面に設置させる
				m_position.z = hitPos2.z - tyousei;
			}
			else if (movementThisFrame.z <= 0)
			{
				//当たり判定でずれた分だけ保存する
				movementThisFrame.z += (hitPos2.z + tyousei) - m_position.z;

				m_position.z = hitPos2.z + tyousei;
			}
			m_position.y -= 2.0f;
		}
		else
		{
			m_position.y -= 2.0f;
		}
	}

	{
		float hitDist2 = fabs(movementThisFrame.z);
		D3DXVECTOR3 hitPos2(m_position);
		// 足元基準に当たり判定をとる場合は少し上から判定する
		m_position.y += 0.5f;
		hitPos2.y += 0.5f;
		// 地面との当たり判定(プレイヤーの位置から真下に当たり判定を行う)
		if (m_fbxStage.RayPick(&m_position, &D3DXVECTOR3(0.f, 0.0f, movementThisFrame.z), &hitDist2, &hitPos2) != -1)
		{
			if (movementThisFrame.z > 0) 
			{
				//当たり判定でずれた分だけ保存する
				movementThisFrame.z += (hitPos2.z - tyousei) - m_position.z;

				// 当たった場合はプレイヤーの高さを地面に設置させる
				m_position.z = hitPos2.z - tyousei;
			}
			else if (movementThisFrame.z <= 0)
			{
				//当たり判定でずれた分だけ保存する
				movementThisFrame.z += (hitPos2.z + tyousei) - m_position.z;

				m_position.z = hitPos2.z + tyousei;
			}
			m_position.y -= 0.5f;
		}
		else
		{
			m_position.y -= 0.5f;
		}
	}

	//壁との当たり判定をどうにかできないか検証
	//hitDist = 1.0;
	//D3DXVECTOR3 hitPos2(m_position);
	//D3DXVECTOR3 sabun;
	//hitPos2.y += 1.0f;
	//hitPos2.z += 0.0f;

	//// 地面との当たり判定(プレイヤーの位置から真下に当たり判定を行う)
	//if (m_fbxStage.RayPick(&hitPos2, &D3DXVECTOR3(movementThisFrame.x, 0.0f, movementThisFrame.z), &hitDist, &hitPos2) != -1)//単位ベクトルじゃないと
	//{
	//	// 当たった場合はプレイヤーの位置を壁に設置させる
	//	sabun.x = (m_position.x - (hitPos2.x + m_playerRadius));
	//	sabun.z = (m_position.z - (hitPos2.z + m_playerRadius));
	//	movementThisFrame.x += sabun.x;
	//	movementThisFrame.z += sabun.z;

	//	m_position.x = hitPos2.x + m_playerRadius;
	//	m_position.z = hitPos2.x + m_playerRadius;
	//}
	

	//共有クラスの値の更新
	m_pSharedInformation->SetPlayerPosition(m_position);
	m_pSharedInformation->SetPlayerMovement(movementThisFrame);

	
	// モデルの行列を算出
	D3DXMATRIX rot, trans, scale;
	D3DXMatrixScaling(&scale, m_playerRadius, m_playerRadius, m_playerRadius);
	D3DXMatrixRotationY(&rot,/* D3DXToRadian*/(m_playerDirection));
	D3DXMatrixTranslation(&trans, m_position.x, m_position.y, m_position.z);
	D3DXMatrixMultiply(m_shpere.GetWorld(), &scale, &rot);
	D3DXMatrixMultiply(m_shpere.GetWorld(), m_shpere.GetWorld(), &trans);

	*m_fbxModel.GetWorld() = *m_shpere.GetWorld();

}

//描画する
void Sumahoneko::Render()
{
	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();
	DirectX* pDirectX = GameLib::Instance.GetDirectX();

	// 通常書き込みモードに設定
	pDirectX->SetRenderMode(DirectX::Normal, false);

	// Zテストの比較方法
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// モデルの描画
	m_fbxModel.Render();
	m_fbxStage.Render();

	/*char s[50];
	sprintf_s(s,50,"position.x %f", m_position.x);
	DEBUGFONT->DrawText(50, 50, 0xffffffff, s);
*/
}
