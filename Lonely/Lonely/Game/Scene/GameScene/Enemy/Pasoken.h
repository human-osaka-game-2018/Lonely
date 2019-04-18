/**
* @file Pasoken.h
* @brief Pasokenクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include "EnemyBase.h"

#include "FBX/FBX.h"
#include "../SharedInformation/SharedInformation.h"

enum DESTINATION
{
	DESTINATION1,
	DESTINATION2,
	DESTINATION3
};

/**
* @brief パソコン犬の処理をまとめたクラス
*/
class Pasoken : public EnemyBase
{
public:

	Pasoken();
	~Pasoken();

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
	* @brief 元の位置に戻す関数
	*/
	void RevertPosition();

	int GetDamage() { return m_damage; }

private:

	FbxModel	m_fbxModel;
	Model		m_shpere;

	D3DXVECTOR3 m_destinationPosition;    //!< パソ犬が向かう目的地のポジション
	int         m_destination;            //!< どの目的地か
	float		m_radius;
	float		m_speed;
	float       m_direction;
	int         m_damage;

	SharedInformation* m_pSharedInformation;

};
