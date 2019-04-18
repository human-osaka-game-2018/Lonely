/**
* @file MenuGameStart.h
* @brief MenuGameStartクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include "ObjectManager/Object2DBase.h"

/**
* @brief タイトルメニュ（GAME START）の処理をまとめたクラス
*/
class MenuGameStart : public Object2DBase
{
public:

	MenuGameStart();
	~MenuGameStart();

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
	* @param タイトルメニューの何番のステップか
	*/
	void Update(int step);

	/**
	* @brief 描画関数
	*/
	void Render();

private:

};
