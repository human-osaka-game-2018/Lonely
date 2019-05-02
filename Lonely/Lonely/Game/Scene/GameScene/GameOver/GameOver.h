/**
* @file GameOver.h
* @brief GameOverのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include "ObjectManager/Object.h"

#include "2DHelper/2DHelper.h"
#include "TexStorage/TexStorage.h"
#include "../SharedInformation/SharedInformation.h"
#include "EnumGameOverState.h"

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

	int                m_count = 0;
	DWORD              m_color = 0xffffffff;
	bool               m_finishFeedOut = false;
	int                m_gameOverState = CONTINUE;
				       
	TexStorage*        m_pTexStorage;
	Simple2DVertex     m_vertices[4];   
	Simple2DVertex     m_verticesGameOver[4];   
	Simple2DVertex     m_verticesContinue[4];   
	Simple2DVertex     m_verticesTitle[4];   

	SharedInformation* m_pSharedInformation;

};
