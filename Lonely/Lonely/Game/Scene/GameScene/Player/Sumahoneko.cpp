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

Sumahoneko::Sumahoneko()
	: m_pSharedInformation(SharedInformation::Instance.GetSharedInformation())
	, m_pSoundsManager(GameLib::Instance.GetSoundsManager())
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
	m_fbxModel.Load("../Graphics/fbxModel/smartcat.fbx");
	//m_fbxModel.Load("../Graphics/stage131.fbx");
	m_pFbxStage = m_pSharedInformation->GetStageFbx();
	m_shpere.CreateShpere(32);

	m_position = { -38.f, 20.f, -63.f };
	m_followingPositionExceptY = m_position;
	m_prevPosition = m_position;
	m_pCollision = new CollisionBox(this, PLAYER);

	const TCHAR* filePath = _T("../Sounds/SE/sumahoneko/jump.mp3");
	m_pSoundsManager->AddFile(filePath, _T("jump"));
	const TCHAR* filePath2 = _T("../Sounds/SE/sumahoneko/damageCry.mp3");
	m_pSoundsManager->AddFile(filePath2, _T("damageCry"));
	const TCHAR* filePath3 = _T("../Sounds/SE/sumahoneko/deadCry.mp3");
	m_pSoundsManager->AddFile(filePath3, _T("deadCry"));
	const TCHAR* filePath4 = _T("../Sounds/SE/sumahoneko/damage.mp3");
	m_pSoundsManager->AddFile(filePath4, _T("damage"));
	const TCHAR* filePath5 = _T("../Sounds/SE/sumahoneko/fainted.mp3");
	m_pSoundsManager->AddFile(filePath5, _T("fainted"));


	m_pSoundsManager->Start(_T("GameBGM"), true);

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
	D3DXVECTOR3 vecCameraDirection(m_position.x - cameraPosition.x, m_position.y - cameraPosition.y, m_position.z - cameraPosition.z);

	//ベクトルの大きさを保存する
	float vecSize;
	vecSize = powf((vecCameraDirection.x * vecCameraDirection.x) + (vecCameraDirection.z*vecCameraDirection.z), 0.5);

	//単位ベクトルを出してから、スピードを掛けて、移動量を計算する
	D3DXVECTOR3 movementSpeed = { 0.f,0.f,0.f };
	movementSpeed.x = (vecCameraDirection.x / vecSize) * transSpeed;
	movementSpeed.z = (vecCameraDirection.z / vecSize) * transSpeed;

	//このフレームで移動する量
	D3DXVECTOR3 movementThisFrame = { 0.f,0.f,0.f };

	//移動処理を行う前の値を保存しておく
	m_prevPosition = m_position;
	m_followingPositionExceptY.y = m_position.y;

	if (m_pSharedInformation->GetGameState() == PLAY)
	{
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
			m_lightDirection.x = movementSpeed.x;
			m_lightDirection.z = movementSpeed.z;

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
			m_lightDirection.x = -movementSpeed.x;
			m_lightDirection.z = -movementSpeed.z;

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
			m_lightDirection.x = -movementSpeed.z;
			m_lightDirection.z = +movementSpeed.x;

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
			m_lightDirection.x = +movementSpeed.z;
			m_lightDirection.z = -movementSpeed.x;

			if (m_runs == true)
			{
				movementThisFrame.x += (movementSpeed.z * runSpeed);
				movementThisFrame.z -= (movementSpeed.x * runSpeed);
			}

			m_playerDirection = m_pSharedInformation->GetCameraDirection() + 1.57f;
		}
		if (DIRECT_INPUT->KeyboardIsReleased(DIK_R))
		{
			ChangeLight();
		}

		//落ちる処理
		Fall();
		//ジャンプ処理
		Jump();
		//アプリライトの方向の設定
		SetLightDirection();
		//当たり判定を登録する
		m_pCollisionManager->RegisterCollision(m_pCollision);

		////ステージとの当たり判定
		this->DetectUpCollidingWithStage(&movementThisFrame);
		this->DetectDownCollidingWithStage(&movementThisFrame);
		//this->DetectXCollidingWithStage(&movementThisFrame);
		//this->DetectZCollidingWithStage(&movementThisFrame);

		const float adjustment = 0.5f;
		{
			//多分hitDistはレイの距離の制限
			float hitDist2 = fabsf(movementThisFrame.x) + fabsf(movementThisFrame.z);
			D3DXVECTOR3 hitPos2(m_position);
			// 足元基準に当たり判定をとる場合は少し上から判定する
			m_position.y += 2.0f;
			hitPos2.y += 2.0f;
			// 地面との当たり判定(プレイヤーの位置から真下に当たり判定を行う)
			if (m_pFbxStage->RayPick(&m_position, &D3DXVECTOR3(movementThisFrame.x, 0.0f, movementThisFrame.z), &hitDist2, &hitPos2) != -1)
			{
				if (movementThisFrame.x == 0.f && movementThisFrame.z == 0.f)
				{

				}
				else if (movementThisFrame.x == 0.f && movementThisFrame.z < 0.f)
				{
					m_position.x = hitPos2.x;
					m_position.z = hitPos2.z + adjustment;
				}
				else if (movementThisFrame.x == 0.f && movementThisFrame.z > 0.f)
				{
					m_position.x = hitPos2.x;
					m_position.z = hitPos2.z - adjustment;
				}
				else if (movementThisFrame.x > 0.f && movementThisFrame.z == 0.f)
				{
					m_position.z = hitPos2.z;
					m_position.x = hitPos2.x - adjustment;
				}
				else if (movementThisFrame.x < 0.f && movementThisFrame.z == 0.f)
				{
					m_position.z = hitPos2.z;
					m_position.x = hitPos2.x + adjustment;
				}
				else if (movementThisFrame.x > 0.f && movementThisFrame.z > 0.f)
				{
					m_position.x = hitPos2.x - adjustment;
					m_position.z = hitPos2.z - adjustment;
				}
				else if (movementThisFrame.x > 0.f && movementThisFrame.z < 0.f)
				{
					m_position.x = hitPos2.x - adjustment;
					m_position.z = hitPos2.z + adjustment;
				}
				else if (movementThisFrame.x < 0.f && movementThisFrame.z < 0.f)
				{
					m_position.x = hitPos2.x + adjustment;
					m_position.z = hitPos2.z + adjustment;
				}
				else if (movementThisFrame.x < 0.f && movementThisFrame.z > 0.f)
				{
					m_position.x = hitPos2.x + adjustment;
					m_position.z = hitPos2.z - adjustment;
				}

				m_position.y -= 2.0f;
			}
			else
			{
				m_position.y -= 2.0f;
			}
		}
	}
	//{
	//	float hitDist2 = fabs(movementThisFrame.x);
	//	D3DXVECTOR3 hitPos2(m_position);
	//	// 足元基準に当たり判定をとる場合は少し上から判定する
	//	m_position.y += 0.5f;
	//	hitPos2.y += 0.5f;
	//	// 地面との当たり判定(プレイヤーの位置から真下に当たり判定を行う)
	//	if (m_pFbxStage->RayPick(&m_position, &D3DXVECTOR3(movementThisFrame.x, 0.0f, 0.0f), &hitDist2, &hitPos2) != -1)
	//	{
	//		if (movementThisFrame.x > 0)
	//		{
	//			//当たり判定でずれた分だけ保存する
	//			movementThisFrame.x += (hitPos2.x - adjustment) - m_position.x;
	//			// 当たった場合はプレイヤーの高さを地面に設置させる
	//			m_position.x = hitPos2.x - adjustment;
	//		}
	//		else if (movementThisFrame.x <= 0)
	//		{
	//			//当たり判定でずれた分だけ保存する
	//			movementThisFrame.x += (hitPos2.x + adjustment) - m_position.x;
	//			m_position.x = hitPos2.x + adjustment;
	//		}
	//		m_position.y -= 0.5f;
	//	}
	//	else
	//	{
	//		m_position.y -= 0.5f;
	//	}
	//}

	//{
	//	//多分hitDistはレイの距離の制限
	//	float hitDist2 = fabs(movementThisFrame.z);
	//	D3DXVECTOR3 hitPos2(m_position);
	//	// 足元基準に当たり判定をとる場合は少し上から判定する
	//	m_position.y += 2.0f;
	//	hitPos2.y += 2.0f;
	//	// 地面との当たり判定(プレイヤーの位置から真下に当たり判定を行う)
	//	if (m_pFbxStage->RayPick(&m_position, &D3DXVECTOR3(0.f, 0.0f, movementThisFrame.z), &hitDist2, &hitPos2) != -1)
	//	{
	//		if (movementThisFrame.z > 0) {
	//			//当たり判定でずれた分だけ保存する
	//			movementThisFrame.z += (hitPos2.z - adjustment) - m_position.z;
	//			// 当たった場合はプレイヤーの高さを地面に設置させる
	//			m_position.z = hitPos2.z - adjustment;
	//		}
	//		else if (movementThisFrame.z <= 0)
	//		{
	//			//当たり判定でずれた分だけ保存する
	//			movementThisFrame.z += (hitPos2.z + adjustment) - m_position.z;

	//			m_position.z = hitPos2.z + adjustment;
	//		}
	//		m_position.y -= 2.0f;
	//	}
	//	else
	//	{
	//		m_position.y -= 2.0f;
	//	}
	//}

	//{
	//	float hitDist2 = fabs(movementThisFrame.z);
	//	D3DXVECTOR3 hitPos2(m_position);
	//	// 足元基準に当たり判定をとる場合は少し上から判定する
	//	m_position.y += 0.5f;
	//	hitPos2.y += 0.5f;
	//	// 地面との当たり判定(プレイヤーの位置から真下に当たり判定を行う)
	//	if (m_pFbxStage->RayPick(&m_position, &D3DXVECTOR3(0.f, 0.0f, movementThisFrame.z), &hitDist2, &hitPos2) != -1)
	//	{
	//		if (movementThisFrame.z > 0)
	//		{
	//			//当たり判定でずれた分だけ保存する
	//			movementThisFrame.z += (hitPos2.z - adjustment) - m_position.z;

	//			// 当たった場合はプレイヤーの高さを地面に設置させる
	//			m_position.z = hitPos2.z - adjustment;
	//		}
	//		else if (movementThisFrame.z <= 0)
	//		{
	//			//当たり判定でずれた分だけ保存する
	//			movementThisFrame.z += (hitPos2.z + adjustment) - m_position.z;

	//			m_position.z = hitPos2.z + adjustment;
	//		}
	//		m_position.y -= 0.5f;
	//	}
	//	else
	//	{
	//		m_position.y -= 0.5f;
	//	}
	//}

	//このフレーム内に動いた量をまとめて移動させる
	m_position.x += movementThisFrame.x;
	m_position.y += movementThisFrame.y;
	m_position.z += movementThisFrame.z;

	//Yだけ保存しないのは、OBBのときに上に乗っているかどうかを判定したいため
	m_followingPositionExceptY.x = m_position.x;
	m_followingPositionExceptY.z = m_position.z;

	//共有クラスの値の更新
	m_pSharedInformation->SetPlayerPosition(m_position);
	m_pSharedInformation->SetPlayerMovement(movementThisFrame);

	//ゲームオーバーのアニメーション処理
	AnimateDead();

	// モデルの行列を算出
	D3DXMATRIX rot, rot2, rot3, trans, scale;
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

	//char s[200];
	//sprintf_s(s, 200, "position.y %f gravity %f time %f lightDirect %f", m_position.y, m_gravity, m_jumpingTime, m_lightDirection.x);
	//DEBUGFONT->DrawText(50, 50, 0xffffffff, s);

	//char arrayLight[200];
	//sprintf_s(arrayLight, 200, "X %f, Y %f, Z %f", m_position.x,m_position.y,m_position.z);
	//DEBUGFONT->DrawText(50, 100, 0xffffffff, arrayLight);

	//if (m_damaged == true)
	//{
	//	/*char s[100];
	//	sprintf_s(s, 100, "damaged");
	//	DEBUGFONT->DrawText(50, 200, 0xffffffff, s);*/

	//}
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
		
		if (m_hp >= 0 && m_hp <= 3)
		{
			m_pSoundsManager->Start(_T("damageCry"), false);
			m_pSoundsManager->Start(_T("damage"), false);
		}

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

			bool isSuccess = m_pSoundsManager->Start(_T("jump"), false);
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
		const float adjustment = 0.1f;

		m_position.y += 2.0f;
		hitPos2.y += 2.0f;
		// 地面との当たり判定(プレイヤーの位置から真下に当たり判定を行う)
		if (m_pFbxStage->RayPick(&m_position, &D3DXVECTOR3(movementThisFrame->x, 0.0f, 0.0f), &hitDist2, &hitPos2) != -1)
		{
			if (movementThisFrame->x > 0)
			{
				//当たり判定でずれた分だけ保存する
				movementThisFrame->x += (hitPos2.x - adjustment) - m_position.x;
				// 当たった場合はプレイヤーの高さを地面に設置させる
				m_position.x = hitPos2.x - adjustment;
			}
			else if (movementThisFrame->x <= 0)
			{
				//当たり判定でずれた分だけ保存する
				movementThisFrame->x += (hitPos2.x + adjustment) - m_position.x;
				m_position.x = hitPos2.x + adjustment;
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
		const float adjustment = 0.1f;

		m_position.y += 0.5f;
		hitPos2.y += 0.5f;
		// 地面との当たり判定(プレイヤーの位置から真下に当たり判定を行う)
		if (m_pFbxStage->RayPick(&m_position, &D3DXVECTOR3(movementThisFrame->x, 0.0f, 0.0f), &hitDist2, &hitPos2) != -1)
		{
			if (movementThisFrame->x > 0)
			{
				//当たり判定でずれた分だけ保存する
				movementThisFrame->x += (hitPos2.x - adjustment) - m_position.x;
				// 当たった場合はプレイヤーの高さを地面に設置させる
				m_position.x = hitPos2.x - adjustment;
			}
			else if (movementThisFrame->x <= 0)
			{
				//当たり判定でずれた分だけ保存する
				movementThisFrame->x += (hitPos2.x + adjustment) - m_position.x;
				m_position.x = hitPos2.x + adjustment;
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
		const float adjustment = 0.1f;

		m_position.y += 2.0f;
		hitPos2.y += 2.0f;
		// 地面との当たり判定(プレイヤーの位置からZ方向に当たり判定を行う)
		if (m_pFbxStage->RayPick(&m_position, &D3DXVECTOR3(0.f, 0.0f, movementThisFrame->z), &hitDist2, &hitPos2) != -1)
		{
			if (movementThisFrame->z > 0) {
				//当たり判定でずれた分だけ保存する
				movementThisFrame->z += (hitPos2.z - adjustment) - m_position.z;
				// 当たった場合はプレイヤーの高さを地面に設置させる
				m_position.z = hitPos2.z - adjustment;
			}
			else if (movementThisFrame->z <= 0)
			{
				//当たり判定でずれた分だけ保存する
				movementThisFrame->z += (hitPos2.z + adjustment) - m_position.z;

				m_position.z = hitPos2.z + adjustment;
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
		const float adjustment = 0.1f;

		m_position.y += 0.5f;
		hitPos2.y += 0.5f;
		// 地面との当たり判定(プレイヤーの位置からZ方向に当たり判定を行う)
		if (m_pFbxStage->RayPick(&m_position, &D3DXVECTOR3(0.f, 0.0f, movementThisFrame->z), &hitDist2, &hitPos2) != -1)
		{
			if (movementThisFrame->z > 0)
			{
				//当たり判定でずれた分だけ保存する
				movementThisFrame->z += (hitPos2.z - adjustment) - m_position.z;

				// 当たった場合はプレイヤーの高さを地面に設置させる
				m_position.z = hitPos2.z - adjustment;
			}
			else if (movementThisFrame->z <= 0)
			{
				//当たり判定でずれた分だけ保存する
				movementThisFrame->z += (hitPos2.z + adjustment) - m_position.z;

				m_position.z = hitPos2.z + adjustment;
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

		if (m_rotation.y > 0)
		{
			m_rotation.y -= 0.01f;
		}
		else
		{
			m_rotation.y += 0.01f;
		}

		if (m_radian >= 8.85/*15.8*/)
		{
			//m_radian = 0.f;
			m_dyingAnimeState = TWO;
			bool isSuccess = m_pSoundsManager->Start(_T("deadCry"), false);
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
			m_pSharedInformation->SetGameState(GAMEOVER);
			m_pSoundsManager->Start(_T("fainted"), false);
		}
	}
}

void Sumahoneko::SetLightDirection()
{
	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();

	if (m_position.x <= -120)//暗い部屋の座標がX<120のため
	{
		pDevice->SetRenderState(D3DRS_AMBIENT, 0x00202020);
	}
	else
	{
		pDevice->SetRenderState(D3DRS_AMBIENT, 0x00808080);
	}

	if (m_usesLight == false)
	{
		pDevice->LightEnable(1, false);
		pDevice->LightEnable(2, false);
		pDevice->LightEnable(3, false);
		return;
	}

	//SPOTライト
	D3DLIGHT9 lightSpot;
	ZeroMemory(&lightSpot, sizeof(D3DLIGHT9));
	lightSpot.Type = D3DLIGHT_SPOT;
	lightSpot.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	lightSpot.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	lightSpot.Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
	lightSpot.Position = m_position;
	lightSpot.Position.y += 2.0f;
	//lightSpot.Direction = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_lightDirection.y = -0.02f;
	D3DXVec3Normalize(&m_lightDirection, &m_lightDirection);
	lightSpot.Direction = m_lightDirection;
	lightSpot.Range = 100.f;
	lightSpot.Falloff = 1.0f;
	lightSpot.Attenuation0 = 1.0f;
	lightSpot.Theta = D3DXToRadian(30.f);
	lightSpot.Phi = D3DXToRadian(60.0f);

	D3DLIGHT9 lightSpotToSumahoneko;
	ZeroMemory(&lightSpotToSumahoneko, sizeof(D3DLIGHT9));
	lightSpotToSumahoneko.Type = D3DLIGHT_SPOT;
	lightSpotToSumahoneko.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	lightSpotToSumahoneko.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	lightSpotToSumahoneko.Ambient = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
	lightSpotToSumahoneko.Position = m_position;
	lightSpotToSumahoneko.Position.y += 2.0f;
	D3DXVec3Normalize(&m_lightDirection, &m_lightDirection);
	lightSpot.Direction = m_lightDirection;
	lightSpotToSumahoneko.Range = 5.f;
	lightSpotToSumahoneko.Falloff = 3.0f;
	lightSpotToSumahoneko.Attenuation0 = 1.0f;
	lightSpotToSumahoneko.Theta = D3DXToRadian(90.f);
	lightSpotToSumahoneko.Phi = D3DXToRadian(180.0f);

	D3DLIGHT9 lightSpotToSumahoneko2;
	ZeroMemory(&lightSpotToSumahoneko2, sizeof(D3DLIGHT9));
	lightSpotToSumahoneko2.Type = D3DLIGHT_SPOT;
	lightSpotToSumahoneko2.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	lightSpotToSumahoneko2.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	lightSpotToSumahoneko2.Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
	lightSpotToSumahoneko2.Position = m_position;
	lightSpotToSumahoneko2.Position.y += 3.0f;
	lightSpotToSumahoneko2.Direction = D3DXVECTOR3(-0.2f, -1.0f, -0.2f);
	lightSpotToSumahoneko2.Range = 5.f;
	lightSpotToSumahoneko2.Falloff = 1.0f;
	lightSpotToSumahoneko2.Attenuation0 = 1.0f;
	lightSpotToSumahoneko2.Theta = D3DXToRadian(10.f);
	lightSpotToSumahoneko2.Phi = D3DXToRadian(30.0f);

	pDevice->SetLight(1, &lightSpot);
	pDevice->LightEnable(1, true);

	pDevice->SetLight(2, &lightSpotToSumahoneko);
	pDevice->LightEnable(2, true);

	pDevice->SetLight(3, &lightSpotToSumahoneko2);
	pDevice->LightEnable(3, true);
}
