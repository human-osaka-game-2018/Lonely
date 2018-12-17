/**
* @file GameScene.h
* @brief GameSceneクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include "../../../GameLib/SceneManager/SceneBase/SceneBase.h"
#include "SharedInformation/SharedInformation.h"


#ifdef  _DEBUG
#pragma comment(lib, "../../../SoundLib/Lib/SoundLibDebug.lib")

#else
#pragma comment(lib, "../../../SoundLib/Lib/SoundLibRelease.lib")
#endif // _DEBUG

#include "../../../SoundLib/Include/SoundsManager.h"
#include "../../../SoundLib/Include/SoundLibCWrapper.h"


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
	
	SharedInformation m_sharedInformation;    //!< 共有クラスの実体

	SoundLib::SoundsManager soundsManager;

};
