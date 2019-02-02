/**
* @file Sumahoneko.cpp
* @brief Sumahonekoクラスのソースファイル
* @author shion-sagawa
*/

#include "Sumahoneko.h"
#include "../../../../GameLib/GameLib.h"
#include "../SharedInformation/EnumGameState.h"
#include "../../../../GameLib/CollisionManager/CollisionBase/CollisionBox.h"
#include "../../../../GameLib/CollisionManager/EnumCollision/Enum_CollisionType.h"
#include "../../../../GameLib/CollisionManager/EnumCollision/Enum_CollisionShape.h"
#include "../SharedInformation/EnumGameState.h"

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
	m_fbxModel.Load("../Graphics/smartcat.fbx");
	//m_fbxModel.Load("../Graphics/stage131.fbx");
	m_pFbxStage = m_pSharedInformation->GetStageFbx();
	m_shpere.CreateShpere(32);


	m_position = { 0.f, 2.f, 0.f };
	m_followingPositionExceptY = m_position;
	m_prevPosition = m_position;
	m_pCollision = new CollisionBox(this, PLAYER);

	return true;
}

//解放する
void Sumahoneko::Finalize()
{
	m_fbxModel.Finalize();
	m_shpere.Finalize();
}

//更新する
void Sumahoneko::Update()
{
	if (m_pSharedInformation->GetGameState() == PAUSE)
	{
		return;
	}


	UpdateDamageCount();

	//スピードを決める
	float transSpeed = 0.1f;
	const float runSpeed = 2.0f;

	//カメラの位置を取得する
	D3DXVECTOR3 cameraPosition = m_pSharedInformation->GetCameraPosition();
	//カメラの方向ベクトルを求める
	D3DXVECTOR3 vecCameraDirection(m_position.x - cameraPosition.x, m_position.y -cameraPosition.y, m_position.z - cameraPosition.z);

	//ベクトルの大きさを保存する
	float vecSize;
	vecSize = powf((vecCameraDirection.x * vecCameraDirection.x) + (vecCameraDirection.z*vecCameraDirection.z), 0.5);

	//単位ベクトルを出してから、スピードを掛けて、移動量を計算する
	D3DXVECTOR3 movementSpeed = {0.f,0.f,0.f};
	movementSpeed.x = (vecCameraDirection.x / vecSize) * transSpeed;
	movementSpeed.z = (vecCameraDirection.z / vecSize) * transSpeed;

	//このフレームで移動する量
	D3DXVECTOR3 movementThisFrame = { 0.f,0.f,0.f };

	//移動処理を行う前の値を保存しておく
	m_prevPosition = m_position;
	m_followingPositionExceptY.y = m_position.y;
	
	//移動量を「歩き」にする
	m_runs = false;
	if (DIRECT_INPUT->KeyboardIsHeld(DIK_RSHIFT))
	{
		//移動量を「走り」にする
		m_runs = true;
	}

	//キー入力で移動
	if (DIRECT_INPUT->KeyboardIsHeld(DIK_W))
	{
		//移動量を保存
		movementThisFrame.x += movementSpeed.x;
		movementThisFrame.z += movementSpeed.z;
		if (m_runs == true)
		{
			movementThisFrame.x += movementSpeed.x * runSpeed;
			movementThisFrame.z += movementSpeed.z * runSpeed;
		}
		
		//キャラの向きを変える
		m_playerDirection = m_pSharedInformation->GetCameraDirection();

	}
	if (DIRECT_INPUT->KeyboardIsHeld(DIK_S))
	{
		movementThisFrame.x -= movementSpeed.x;
		movementThisFrame.z -= movementSpeed.z;
		if (m_runs == true)
		{
			movementThisFrame.x -= (movementSpeed.x * runSpeed);
			movementThisFrame.z -= (movementSpeed.z * runSpeed);
		}
		
		m_playerDirection = m_pSharedInformation->GetCameraDirection() + 3.14f;
	}
	if (DIRECT_INPUT->KeyboardIsHeld(DIK_A))
	{
		movementThisFrame.x -= movementSpeed.z;
		movementThisFrame.z += movementSpeed.x;
		if (m_runs == true)
		{
			movementThisFrame.x -= (movementSpeed.z * runSpeed);
			movementThisFrame.z += (movementSpeed.x * runSpeed);
		}
		
		m_playerDirection = m_pSharedInformation->GetCameraDirection() - 1.57f;
	}
	if (DIRECT_INPUT->KeyboardIsHeld(DIK_D))
	{
		movementThisFrame.x += movementSpeed.z;
		movementThisFrame.z -= movementSpeed.x;
		if (m_runs == true)
		{
			movementThisFrame.x += (movementSpeed.z * runSpeed);
			movementThisFrame.z -= (movementSpeed.x * runSpeed);
		}
		
		m_playerDirection = m_pSharedInformation->GetCameraDirection() + 1.57f;
	}

	//落ちる処理
	Fall();
	//ジャンプ処理
	Jump();
	//ゲームオーバーのアニメーション処理
	AnimateDead();
	//当たり判定を登録する
	m_pCollisionManager->RegisterCollision(m_pCollision);

	////ステージとの当たり判定
	this->DetectUpCollidingWithStage(&movementThisFrame);
	this->DetectDownCollidingWithStage(&movementThisFrame);
	//this->DetectXCollidingWithStage(&movementThisFrame);
	//this->DetectZCollidingWithStage(&movementThisFrame);

	////多分hitDistはレイの距離の制限
	//float hitDist = 10.0f;
	//D3DXVECTOR3 hitPos(m_position);
	//// 足元基準に当たり判定をとる場合は少し上から判定する
	//m_position.y += 1.0f;
	//hitPos.y += 1.0f;
	//// 地面との当たり判定(プレイヤーの位置から真下に当たり判定を行う)
	//if (m_pFbxStage->RayPick(&m_position, &D3DXVECTOR3(0.0f, -1.0f, 0.0f), &hitDist, &hitPos) != -1)
	//{
	//	// 当たった場合はプレイヤーの高さを地面に設置させる
	//	m_position.y = hitPos.y + m_radius;
	//}
	//else
	//{
	//	m_position.y -= 1.0f;
	//}

	const float tyousei = 0.5f;
	{
		//多分hitDistはレイの距離の制限
		float hitDist2 = fabs(movementThisFrame.x);
		D3DXVECTOR3 hitPos2(m_position);
		// 足元基準に当たり判定をとる場合は少し上から判定する
		m_position.y += 2.0f;
		hitPos2.y += 2.0f;
		// 地面との当たり判定(プレイヤーの位置から真下に当たり判定を行う)
		if (m_pFbxStage->RayPick(&m_position, &D3DXVECTOR3(movementThisFrame.x, 0.0f, 0.0f), &hitDist2, &hitPos2) != -1)
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
		if (m_pFbxStage->RayPick(&m_position, &D3DXVECTOR3(movementThisFrame.x, 0.0f, 0.0f), &hitDist2, &hitPos2) != -1)
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
		if (m_pFbxStage->RayPick(&m_position, &D3DXVECTOR3(0.f, 0.0f, movementThisFrame.z), &hitDist2, &hitPos2) != -1)
		{
			if (movementThisFrame.z > 0) {
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
		if (m_pFbxStage->RayPick(&m_position, &D3DXVECTOR3(0.f, 0.0f, movementThisFrame.z), &hitDist2, &hitPos2) != -1)
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

	//スマホ猫を移動させる
	m_position.x += movementThisFrame.x;
	m_position.y += movementThisFrame.y;
	m_position.z += movementThisFrame.z;

	//XZだけ動いた後の位置を保存する、Yは動いていない位置を保存する
	m_followingPositionExceptY.x = m_position.x;
	m_followingPositionExceptY.z = m_position.z;

	//共有クラスの値の更新
	m_pSharedInformation->SetPlayerPosition(m_position);
	m_pSharedInformation->SetPlayerMovement(movementThisFrame);
	
	// モデルの行列を算出
	D3DXMATRIX rot,rot2, rot3,trans, scale;
	D3DXMatrixScaling(&scale, m_radius, m_radius, m_radius);
	if (m_dead == false)
	{
		D3DXMatrixRotationY(&rot, (m_playerDirection));
	}
	else
	{
		D3DXMatrixRotationX(&rot, (m_rotation.x));
		D3DXMatrixRotationY(&rot2, (m_rotation.y));
		D3DXMatrixMultiply(&rot, &rot, &rot2);
		D3DXMatrixRotationZ(&rot3, (m_rotation.z));
		D3DXMatrixMultiply(&rot, &rot, &rot3);
	}

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
	
	char s[100];
	sprintf_s(s,100,"position.y %f gravity %f time %f", m_position.y, m_gravity, m_jumpingTime);
	DEBUGFONT->DrawText(50, 50, 0xffffffff, s);

	if (m_damaged == true)
	{
		char s[100];
		sprintf_s(s, 100, "damaged");
		DEBUGFONT->DrawText(50, 200, 0xffffffff, s);

	}
}

void Sumahoneko::RevertPositionY()
{
	//Yだけ移動する前の位置に戻す
	m_position.y = m_prevPosition.y;
	//移動量をYだけゼロにする、カメラだけ移動してしまうのを防ぐため
	D3DXVECTOR3 movement;
	movement = m_pSharedInformation->GetPlayerMovement();
	movement.y = 0.f;
	m_pSharedInformation->SetPlayerMovement(movement);
}

void Sumahoneko::RevertPosition()
{
	//移動する前の位置に戻す
	m_position = m_prevPosition;
	m_followingPositionExceptY = m_prevPosition;
	
	//移動量をゼロにする、カメラだけ移動してしまうのを防ぐため
	D3DXVECTOR3 movement = { 0.f,0.f,0.f };
	m_pSharedInformation->SetPlayerMovement(movement);
}

void Sumahoneko::Fall()
{
	//着地していたら重力を０にする
	if (m_isLanded == true)
	{
		m_gravity = -2.f;
		m_jumpingTime = 0;
	}
	else
	{
		++m_jumpingTime;
		//重力　 ＝　 経過時間　　*　　　重力加速度　   
		m_gravity -= m_jumpingTime * m_accelerationGravity;

		if (m_gravity <= m_maxGravity)
		{
			m_gravity = m_maxGravity;
		}
	}
}

void Sumahoneko::Damaged()
{
	if (m_damaged == false)
	{
		m_damaged = true;
		m_damageCount = 60;
		m_hp -= 1;
		m_pSharedInformation->SetHp(m_hp);

		if (m_hp == 0)
		{
			m_dead = true;
			m_pSharedInformation->SetGameState(DEAD);
		}
	}
}

void Sumahoneko::UpdateDamageCount()
{
	if (m_damaged == true) 
	{
		--m_damageCount;
		if (m_damageCount <= 0)
		{
			m_damaged = false;
		}
	}

}

void Sumahoneko::Jump()
{
	//着地している状態
	if (m_isLanded == true) 
	{
		if (DIRECT_INPUT->KeyboardIsReleased(DIK_SPACE))
		{
			//重力　 ＝　    初速度
			m_gravity = m_initialVelocity;
			m_isLanded = false;
		}
	}
}

void Sumahoneko::DetectUpCollidingWithStage(D3DXVECTOR3* movementThisFrame)
{
	//移動方向が上の時のステージとの当たり判定
	D3DXVECTOR3 hitPos(m_position);
	//レイの長さ
	float hitDist = m_gravity;
	// レイの始点を頭の位置まで上げる
	m_position.y += 2.0f;
	hitPos.y += 2.0f;
	// 天井との当たり判定(プレイヤーの位置から真上に当たり判定を行う)
	if (m_gravity > 0) 
	{
		if (m_pFbxStage->RayPick(&m_position, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), &hitDist, &hitPos) != -1)
		{
			//レイの衝突判定でずらした量 + スマホ猫の大きさ　を保存する
			movementThisFrame->y -= (hitPos.y - m_position.y) + 2.0f;
			// 当たった場合はプレイヤーの高さを天井ギリギリに移動させる
			m_position.y = hitPos.y;
			//上向きの重力を打ち消す
			m_gravity = 0.f;
		}
		else
		{
			movementThisFrame->y += m_gravity;
			// レイの始点のために調整した分をもとに戻す
			m_position.y -= 2.0f;
		}
	}
	else 
	{
		// レイの始点のために調整した分をもとに戻す
		m_position.y -= 2.0f;
	}
}

void Sumahoneko::DetectDownCollidingWithStage(D3DXVECTOR3* movementThisFrame)
{
	//移動方向が下の時のステージとの当たり判定
	D3DXVECTOR3 hitPos(m_position);
	//レイの長さ
	float hitDist = 0.f;
	hitDist -= m_gravity;
	// レイの始点を腰の位置まで上げる
	m_position.y += 1.0f;
	hitPos.y += 1.0f;
	// 地面との当たり判定(プレイヤーの位置から真上に当たり判定を行う)
	if (m_gravity < 0) {
		if (m_pFbxStage->RayPick(&m_position, &D3DXVECTOR3(0.0f, -1.0f, 0.0f), &hitDist, &hitPos) != -1)
		{
			//着地したことを保存する
			m_isLanded = true;
			// 当たった場合はプレイヤーの高さを地面より少し上に設置させる
			m_position.y = hitPos.y + 0.1f;
			m_jumpingTime = 0.f;
		}
		else
		{
			if (m_isLanded == true)
			{
				//isLanded＝falseがないと、崖から落下しなくなる
				m_isLanded = false;
				m_gravity = 0.f;
			}
			movementThisFrame->y += m_gravity;
			// レイの始点のために調整した分をもとに戻す
			m_position.y -= 1.0f;
		}
	}
	else
	{
		// レイの始点のために調整した分をもとに戻す
		m_position.y -= 1.0f;
	}
}

void Sumahoneko::DetectXCollidingWithStage(D3DXVECTOR3* movementThisFrame)
{
	//キャラの頭辺りからレイを飛ばす
	{
		float hitDist2 = fabs(movementThisFrame->x);
		D3DXVECTOR3 hitPos2(m_position);
		const float tyousei = 0.1f;
		
		m_position.y += 2.0f;
		hitPos2.y += 2.0f;
		// 地面との当たり判定(プレイヤーの位置から真下に当たり判定を行う)
		if (m_pFbxStage->RayPick(&m_position, &D3DXVECTOR3(movementThisFrame->x, 0.0f, 0.0f), &hitDist2, &hitPos2) != -1)
		{
			if (movementThisFrame->x > 0)
			{
				//当たり判定でずれた分だけ保存する
				movementThisFrame->x += (hitPos2.x - tyousei) - m_position.x;
				// 当たった場合はプレイヤーの高さを地面に設置させる
				m_position.x = hitPos2.x - tyousei;
			}
			else if (movementThisFrame->x <= 0)
			{
				//当たり判定でずれた分だけ保存する
				movementThisFrame->x += (hitPos2.x + tyousei) - m_position.x;
				m_position.x = hitPos2.x + tyousei;
			}
			m_position.y -= 2.0f;
		}
		else
		{
			m_position.y -= 2.0f;
		}
	}

	//キャラの腰辺りからレイを飛ばす
	{
		float hitDist2 = fabs(movementThisFrame->x);
		D3DXVECTOR3 hitPos2(m_position);
		const float tyousei = 0.1f;
		
		m_position.y += 0.5f;
		hitPos2.y += 0.5f;
		// 地面との当たり判定(プレイヤーの位置から真下に当たり判定を行う)
		if (m_pFbxStage->RayPick(&m_position, &D3DXVECTOR3(movementThisFrame->x, 0.0f, 0.0f), &hitDist2, &hitPos2) != -1)
		{
			if (movementThisFrame->x > 0)
			{
				//当たり判定でずれた分だけ保存する
				movementThisFrame->x += (hitPos2.x - tyousei) - m_position.x;
				// 当たった場合はプレイヤーの高さを地面に設置させる
				m_position.x = hitPos2.x - tyousei;
			}
			else if (movementThisFrame->x <= 0)
			{
				//当たり判定でずれた分だけ保存する
				movementThisFrame->x += (hitPos2.x + tyousei) - m_position.x;
				m_position.x = hitPos2.x + tyousei;
			}
			m_position.y -= 0.5f;
		}
		else
		{
			m_position.y -= 0.5f;
		}
	}
}

void Sumahoneko::DetectZCollidingWithStage(D3DXVECTOR3* movementThisFrame)
{
	//キャラの頭辺りからレイを飛ばす
	{
		float hitDist2 = fabs(movementThisFrame->z);
		D3DXVECTOR3 hitPos2(m_position);
		const float tyousei = 0.1f;

		m_position.y += 2.0f;
		hitPos2.y += 2.0f;
		// 地面との当たり判定(プレイヤーの位置からZ方向に当たり判定を行う)
		if (m_pFbxStage->RayPick(&m_position, &D3DXVECTOR3(0.f, 0.0f, movementThisFrame->z), &hitDist2, &hitPos2) != -1)
		{
			if (movementThisFrame->z > 0) {
				//当たり判定でずれた分だけ保存する
				movementThisFrame->z += (hitPos2.z - tyousei) - m_position.z;
				// 当たった場合はプレイヤーの高さを地面に設置させる
				m_position.z = hitPos2.z - tyousei;
			}
			else if (movementThisFrame->z <= 0)
			{
				//当たり判定でずれた分だけ保存する
				movementThisFrame->z += (hitPos2.z + tyousei) - m_position.z;

				m_position.z = hitPos2.z + tyousei;
			}
			m_position.y -= 2.0f;
		}
		else
		{
			m_position.y -= 2.0f;
		}
	}

	//キャラの頭辺りからレイを飛ばす
	{
		float hitDist2 = fabs(movementThisFrame->z);
		D3DXVECTOR3 hitPos2(m_position);
		const float tyousei = 0.1f;
		
		m_position.y += 0.5f;
		hitPos2.y += 0.5f;
		// 地面との当たり判定(プレイヤーの位置からZ方向に当たり判定を行う)
		if (m_pFbxStage->RayPick(&m_position, &D3DXVECTOR3(0.f, 0.0f, movementThisFrame->z), &hitDist2, &hitPos2) != -1)
		{
			if (movementThisFrame->z > 0)
			{
				//当たり判定でずれた分だけ保存する
				movementThisFrame->z += (hitPos2.z - tyousei) - m_position.z;

				// 当たった場合はプレイヤーの高さを地面に設置させる
				m_position.z = hitPos2.z - tyousei;
			}
			else if (movementThisFrame->z <= 0)
			{
				//当たり判定でずれた分だけ保存する
				movementThisFrame->z += (hitPos2.z + tyousei) - m_position.z;

				m_position.z = hitPos2.z + tyousei;
			}
			m_position.y -= 0.5f;
		}
		else
		{
			m_position.y -= 0.5f;
		}
	}
}

void Sumahoneko::AnimateDead()
{
	if (m_dead == false)
	{
		return;
	}

	if (m_dyingAnimeState == ONE)
	{
		m_radian += 0.1f;
		m_rotation.x = 0.5f * cos(m_radian);
		m_rotation.z = 0.5f * sin(m_radian);
		m_rotation.y = m_playerDirection;

		if (m_radian >= 8.85/*15.8*/)
		{
			//m_radian = 0.f;
			m_dyingAnimeState = TWO;
		}
	}
	if (m_dyingAnimeState == TWO)
	{
		m_radian += 0.1f - m_dyingAnimeCount * 0.001f;
		m_rotation.x = 0.5f * cos(m_radian);
		m_rotation.z = 0.5f * sin(m_radian);
		//m_rotation.z += 0.2f;

		++m_dyingAnimeCount;

		if (m_dyingAnimeCount > 60) 
		{
			m_dyingAnimeState = THREE;
			m_dyingAnimeCount = 0;
		}
	}
	if (m_dyingAnimeState == THREE)
	{
		++m_dyingAnimeCount;
		m_rotation.x -= 0.004f * static_cast<float>(m_dyingAnimeCount);
		if (m_rotation.x <= -1.50)
		{
			m_rotation.z = 0.f;
			m_dyingAnimeState = FOUR;
		}
	}
}
