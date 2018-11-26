/**
* @file TitleBackGround.h
* @brief TitleBackGroundクラスのヘッダファイル
* @author 佐川　嗣苑
*/

#pragma once

#include "../../../GameLib/ObjectManager/Object.h"
#include "../../../GameLib/DirectX/DirectX.h"
#include "../../../GameLib/2DHelper/2DHelper.h"
#include "../../../GameLib/FBX/VertexBuffer.h"


/**
* @brief タイトルの背景関係の処理をまとめたクラス
*/
class TitleBackGround : public Object
{
public:
	
	TitleBackGround();
	~TitleBackGround();

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

	Texture       m_texture;
	VertexBuffer  m_vertexBuffer;
};
