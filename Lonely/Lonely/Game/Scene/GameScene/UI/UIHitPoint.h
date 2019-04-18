﻿/**
* @file UIHitPoint.h
* @brief UIHitPointクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include "ObjectManager/Object2DBase.h"

#include "Scene/GameScene/SharedInformation/SharedInformation.h"

/**
* @brief UIのHP関係をまとめたクラス
*/
class UIHitPoint : public Object2DBase
{
public:

	UIHitPoint();
	~UIHitPoint();

	/**
	* @brief 初期化する関数
	* @return 初期化に異常があるとFALSE
	*/
	bool Initialize();

	/**
	* @brief 解放する関数
	*/
	void Finalize();

	/**
	* @brief 操作関数
	*/
	void Update();

	/**
	* @brief 描画関数
	*/
	void Render();

private:

	SharedInformation* m_pSharedInformation;
	int                m_hp;
};
