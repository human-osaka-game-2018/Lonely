/**
* @file TitleBackGround.h
* @brief TitleBackGroundクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include "../../../GameLib/ObjectManager/Object2DBase.h"
#include "../../../GameLib/DirectX/DirectX.h"
#include "../../../GameLib/2DHelper/2DHelper.h"
#include "../../../GameLib/FBX/Texture.h"


/**
* @brief タイトルの背景関係の処理をまとめたクラス
*/
class TitleBackGround : public Object2DBase
{
public:
	
	TitleBackGround();
	~TitleBackGround();

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
	*/
	void Update();

	/**
	* @brief 描画関数
	*/
	void Render();

private:

};
