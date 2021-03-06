﻿/**
* @file MenuCursor.h
* @brief MenuCursorクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include "ObjectManager/Object2DBase.h"

/**
* @brief タイトルメニュ（GAME END）の処理をまとめたクラス
*/
class MenuCursor : public Object2DBase
{
public:

	MenuCursor();
	~MenuCursor();

	/**
	* @brief 初期化する関数
	* @return 初期化が上手くできていないとFALSE
	*/
	bool Initialize();

	/**
	* @brief 解放する関数
	*/
	void Finalize();

	/**
	* @brief 操作関数
	* @param タイトルメニューの何番のステップか
	*/
	void Update(int step);

	/**
	* @brief 描画関数
	*/
	void Render();

private:

};
