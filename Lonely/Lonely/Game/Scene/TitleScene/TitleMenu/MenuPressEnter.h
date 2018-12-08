/**
* @file MenuPressEnter.h
* @brief MenuPressEnterクラスのヘッダファイル
* @author 佐川　嗣苑
*/

#pragma once

#include "../../../../GameLib/ObjectManager/Object2DBase.h"
#include "../../../../GameLib/DirectX/DirectX.h"
#include "../../../../GameLib/2DHelper/2DHelper.h"
#include "../../../../GameLib/FBX/Texture.h"


/**
* @brief タイトルメニュ（PRESS　ENTER）の処理をまとめたクラス
*/
class MenuPressEnter : public Object2DBase
{
public:

	MenuPressEnter();
	~MenuPressEnter();


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

	int            frameCount = 0;     //!< フレームを数えるための変数
};
