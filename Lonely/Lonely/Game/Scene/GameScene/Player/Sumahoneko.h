
/**
* @file Sumahoneko.h
* @brief Sumahonekoクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include "PlayerBase.h"

#include "../../../../GameLib/FBX/FBX.h"
#include "../SharedInformation/SharedInformation.h"
#include "../../../../GameLib/GameLib.h"

enum DYING_ANIME_STATE
{
	ONE,
	TWO,
	THREE,
	FOUR
};

/**
* @brief プレイヤー関係の処理をまとめたクラス
*/
class Sumahoneko : public PlayerBase
{
public:

	Sumahoneko();
	~Sumahoneko();

	/**
	* @brief 初期化関数
	*/
	bool Initialize();
	/**
	* @brief 解放関数
	*/
	void Finalize();

	/**
	* @brief 更新を行う関数
	*/
	void Update();

	/**
	* @brief 描画を行う関数
	*/
	void Render();

	/**
	* @brief フレームで処理した移動量を、衝突していたので戻す関数
	*/
	void RevertPosition();

	/**
	* @brief フレームで処理したY軸移動量を、衝突していたので戻す関数
	*/
	void RevertPositionY();

	/**
	* @brief スマホ猫が落下している関数
	*/
	void Fall();

	/**
	* @brief ジャンプを行う関数
	*/
	void Jump();

	/**
	* @brief ダメージを受けている関数
	*/
	void Damaged();

	/**
	* @brief ダメージ受けて無敵時間を数える関数
	*/
	void UpdateDamageCount();

	/**
	* @brief 死ぬときのアニメーションを行う関数
	*/
	void AnimateDead();

	/**
	* @brief ライトモードを切り替える関数
	*/
	void ChangeLight() { m_usesLight = !m_usesLight; }

	/**
	* @brief ライトの方向を設定する関数
	*/
	void SetLightDirection();

	void SetIsLanded(bool isLanded) { m_isLanded = isLanded; }

private:

	void DetectUpCollidingWithStage(D3DXVECTOR3* movementThisFrame);

	void DetectDownCollidingWithStage(D3DXVECTOR3* movementThisFrame);

	void DetectXCollidingWithStage(D3DXVECTOR3* movementThisFrame);

	void DetectZCollidingWithStage(D3DXVECTOR3* movementThisFrame);

	FbxModel	m_fbxModel;
	Model		m_shpere;
	float		m_radius = 0.1f;
	float       m_playerDirection = 0.f;
	float       m_gravity = 0.f;
	float       m_maxGravity = -5.f;
	float       m_jumpingTime = 0.f;
	float       m_accelerationGravity = 0.0025f;
	float       m_initialVelocity = 0.5f;

	D3DXVECTOR3 m_rotation = { 0.f,0.f,0.f };
	D3DXVECTOR3 m_lightDirection = { 0.f,0.f,1.f };
	//float       m_accelerationGravity = 0.0001f;
	//float       m_initialVelocity = 1.f;
	bool        m_isLanded = false;
	bool        m_runs = false;
	bool        m_damaged = false;
	bool        m_dead = false;
	bool        m_usesLight = false;
	int         m_hp = 3;
	int         m_damageCount;
	int         m_dyingAnimeState;
	int         m_dyingAnimeCount;
	float       m_radian = 0.f;

	SharedInformation*       m_pSharedInformation;
	SoundLib::SoundsManager* m_pSoundsManager;

	FbxModel*   m_pFbxStage;//今はとりあえずこのクラスに置いているだけ
};
