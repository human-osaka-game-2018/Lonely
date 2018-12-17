
/**
* @file Sumahoneko.h
* @brief Sumahonekoクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include "../../../GameLib/ObjectManager/Object3DBase.h"
#include "../../../GameLib/FBX/FBX.h"
#include "SharedInformation/SharedInformation.h"

/**
* @brief プレイヤー関係の処理をまとめたクラス
*/
class Sumahoneko : public Object3DBase
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

private:

	// ライトの設定
	void SetLight(void);
	// プレイヤーの更新
	void UpdatePlayer(void);

private:

	FbxModel	m_fbxModel;
	Model		m_shpere;
	D3DXVECTOR3 m_position;
	float		m_playerRadius;
	float		m_playerSpeed;
	float       m_playerDirection;

	SharedInformation* m_pSharedInformation;

	FbxModel    m_fbxStage;//今はとりあえずこのクラスに置いているだけ
};
