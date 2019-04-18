/**
* @file TitleLogo.h
* @brief TitleLogoクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include "ObjectManager/Object2DBase.h"

/**
* @brief タイトルロゴの処理をまとめたクラス
*/
class TitleLogo : public Object2DBase
{
public:

	TitleLogo();
	~TitleLogo();


	/**
	* @brief 初期化する関数
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

	float logoWidth = 30.f;     //!< タイトルロゴの中心点からの横幅
	float logoHeight = 40.f;    //!< タイトルロゴの中心点からの縦幅
};
