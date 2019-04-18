/**
* @file GameScene.h
* @brief GameSceneクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include "SceneManager/SceneBase/SceneBase.h"

#include "SoundLib/Include/SoundsManager.h"
#include "SoundLib/Include/SoundLibCWrapper.h"

#include "SharedInformation/SharedInformation.h"
#include "CollisionManager/CollisionManager.h"

/**
* @brief ゲームシーンのクラス
*/
class GameScene : public SceneBase
{
public:

	GameScene();
	~GameScene();

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
	
	SharedInformation        m_sharedInformation;    //!< 共有クラスの実体
	CollisionManager*        m_pCollisionManager;    //!< 当たり判定管理クラスのポインタ
	SoundLib::SoundsManager* m_pSoundsManager;

};
