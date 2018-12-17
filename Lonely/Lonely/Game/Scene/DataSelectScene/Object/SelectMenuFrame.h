/**
* @file SelectMenuFrame.h
* @brief SelectMenuFrameクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include "../../../../GameLib/ObjectManager/Object2DBase.h"
#include "../../../../GameLib/DirectX/DirectX.h"
#include "../SelectCursorInformation/SelectCursorInformation.h"

/**
* @brief セレクトメニューの処理をまとめたクラス
*/
class SelectMenuFrame : public Object2DBase
{
public:

	SelectMenuFrame();
	~SelectMenuFrame();

	explicit SelectMenuFrame(SelectCursorInformation* instance);

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
	Simple2DVertex           m_verticesBackFrame[4];

};


