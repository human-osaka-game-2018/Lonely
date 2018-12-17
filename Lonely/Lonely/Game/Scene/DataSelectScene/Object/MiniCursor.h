/**
* @file MiniCursor.h
* @brief MiniCursorクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include "../../../../GameLib/ObjectManager/Object2DBase.h"
#include "../../../../GameLib/DirectX/DirectX.h"
#include "../SelectCursorInformation/SelectCursorInformation.h"

/**
* @brief ミニカーソルの処理をまとめたクラス
*/
class MiniCursor : public Object2DBase
{
public:

	MiniCursor();
	~MiniCursor();

	explicit MiniCursor(SelectCursorInformation* instance);

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

	SelectCursorInformation * m_pSelectCursorInformation;

};

