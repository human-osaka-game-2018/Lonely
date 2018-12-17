/**
* @file CatCursor.h
* @brief CatCursorクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include "../../../../GameLib/ObjectManager/Object2DBase.h"
#include "../../../../GameLib/DirectX/DirectX.h"
#include "../SelectCursorInformation/SelectCursorInformation.h"

/**
* @brief 猫型カーソルの処理をまとめたクラス
*/
class CatCursor : public Object2DBase
{
public:

	CatCursor();
	~CatCursor();

	explicit CatCursor(SelectCursorInformation* instance);

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

	SelectCursorInformation* m_pSelectCursorInformation;

};
