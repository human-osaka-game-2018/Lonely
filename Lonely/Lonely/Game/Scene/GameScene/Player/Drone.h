/**
* @file Drone.h
* @brief Droneクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include "ObjectManager/Object3DBase.h"
#include "FBX/FBX.h"

/**
* @brief プレイヤー関係の処理をまとめたクラス
*/
class Drone : public Object3DBase
{
public:

	Drone();
	~Drone();

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
	D3DXVECTOR3 m_playerPos;
	float		m_radius;
	float		m_playerSpeed;
};
