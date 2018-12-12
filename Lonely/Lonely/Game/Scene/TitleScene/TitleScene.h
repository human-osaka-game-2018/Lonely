/**
* @file TitleScene.h
* @brief TitleSceneクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include "../../../GameLib/SceneManager/SceneBase/SceneBase.h"

/**
* @brief タイトルシーンのクラス
*/
class TitleScene : public SceneBase
{
public:

	TitleScene();
	~TitleScene();

	/**
	* @brief 初期化関数
	*/
	bool Initialize();

	/**
	* @brief 解放関数
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
