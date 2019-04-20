/**
* @file StoryIntroduction.h
* @brief StoryIntroductionクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include "ObjectManager/Object.h"

#include "TexStorage/TexStorage.h"
#include "2DHelper/2DHelper.h"
#include "Scene/GameScene/SharedInformation/SharedInformation.h"


/**
* @brief 物語背景導入関係の処理をまとめたクラス
*/
class StoryIntroduction : public Object
{
public:

	StoryIntroduction();
	~StoryIntroduction();

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

	static const int TEXTURE_MAX = 9;
	const TCHAR* m_textureKeys[TEXTURE_MAX] = {

		_T("story1"),
		_T("story2"),
		_T("story3"),
		_T("story4"),
		_T("story5"),
		_T("story6"),
		_T("story7"),
		_T("story8"),
		_T("story9")
	};

	Simple2DVertex       m_vertices[4];
	Simple2DVertex       m_verticies[4];

	TexStorage*        m_pTexStorage;
	SharedInformation* m_pSharedInformation;

};
