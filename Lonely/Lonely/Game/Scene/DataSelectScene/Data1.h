/**
* @file Data1.h
* @brief Data1クラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include "../../../GameLib/ObjectManager/Object2DBase.h"
#include "../../../GameLib/DirectX/DirectX.h"

/**
* @brief データ関係の処理をまとめたクラス
*/
class Data1 : public Object2DBase
{
public:

	Data1();
	~Data1();

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
