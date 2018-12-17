/**
* @file DataSelectScene.h
* @brief DataSelectSceneクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include "../../../GameLib/SceneManager/SceneBase/SceneBase.h"
#include "SelectCursorInformation/SelectCursorInformation.h"

/**
* @brief データセレクトシーンのクラス
*/
class DataSelectScene : public SceneBase
{
public:

	DataSelectScene();
	~DataSelectScene();
	
	/**
	* @brief 初期化する関数
	*/
	bool Initialize();

	/**
	* @brief 解放する関数
	*/
	void Finalize();

	/**
	* @brief 操作を更新する関数
	*/
	void Update();

	/**
	* @brief 描画関数
	*/
	void Render();

private:

	SelectCursorInformation m_selectCursorInformation;

};
