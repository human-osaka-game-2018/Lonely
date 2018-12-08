/**
* @file UI.h
* @brief UIのヘッダファイル
* @author 佐川　嗣苑
*/

#pragma once

#include "../../../GameLib/ObjectManager/Object2DBase.h"
#include "../../../GameLib/DirectX/DirectX.h"
#include "../../../GameLib/2DHelper/2DHelper.h"
#include "../../../GameLib/FBX/VertexBuffer.h"
#include "../../../GameLib/FBX/Texture.h"

/**
* @brief UIの処理をまとめたクラス
*/
class UI : public Object2DBase
{
public:

	UI();
	~UI();


	/**
	* @brief 初期化する関数
	* @param
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

	float logoWidth = 30.f;            //!< タイトルロゴの中心点からの横幅
	float logoHeight = 20.f;           //!< タイトルロゴの中心点からの縦幅
};
