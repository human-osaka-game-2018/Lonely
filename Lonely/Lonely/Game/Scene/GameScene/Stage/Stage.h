/**
* @file Stage.h
* @brief Stageクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include "ObjectManager/Object3DBase.h"

#include "FBX/FBX.h"
#include "../SharedInformation/SharedInformation.h"

/**
* @brief ステージの処理をまとめたクラス
*/
class Stage : public Object3DBase
{
public:

	Stage();
	~Stage();

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


	FbxModel* GetFbxModel() { return &m_fbxModel; }

private:

	FbxModel m_fbxModel;  
	Model	 m_shpere;
	float	 m_radius;
	float    m_direction;

	SharedInformation* m_pSharedInformation;
};
