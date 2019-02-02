﻿/**
* @file GameOver.h
* @brief GameOverのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include "../../../../GameLib/ObjectManager/Object.h"
#include "../../../../GameLib/2DHelper/2DHelper.h"
#include "../../../../GameLib/TexStorage/TexStorage.h"
#include "../../../../GameLib/FBX/Texture.h"

/**
* @brief GameOverの処理をまとめたクラス
*/
class GameOver : public Object
{
public:

	GameOver();
	~GameOver();

	/**
	* @brief 初期化する関数
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

	int             m_count = 0;
	DWORD           m_color = 0xffffffff;


	TexStorage*     m_pTexStrage;
	Texture         m_texture;
	Simple2DVertex  m_vertices[4];    //!< 矩形の4頂点

};
