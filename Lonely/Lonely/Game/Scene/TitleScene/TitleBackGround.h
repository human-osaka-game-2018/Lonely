/**
* @file TitleBackground.h
* @brief TitleBackgroundクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include "ObjectManager/Object2DBase.h"

/**
* @brief タイトルの背景関係の処理をまとめたクラス
*/
class TitleBackground : public Object2DBase
{
public:
	
	TitleBackground();
	~TitleBackground();

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

};
