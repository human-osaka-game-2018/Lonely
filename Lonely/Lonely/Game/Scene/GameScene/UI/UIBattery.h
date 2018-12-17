/**
* @file UIBattery.h
* @brief UIBatteryクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include "../../../../GameLib/ObjectManager/Object2DBase.h"
#include "../../../../GameLib/DirectX/DirectX.h"
#include "../../../../GameLib/2DHelper/2DHelper.h"


/**
* @brief 充電関係をまとめたクラス
*/
class UIBattery : public Object2DBase
{
public:

	UIBattery();
	~UIBattery();

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
