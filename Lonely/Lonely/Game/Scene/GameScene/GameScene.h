/**
* @file GameScene.h
* @brief GameSceneクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include <thread>
#include "../../../GameLib/SceneManager/SceneBase/SceneBase.h"
#include "SharedInformation/SharedInformation.h"


#ifdef  _DEBUG
#pragma comment(lib, "SoundLib/Lib/SoundLibDebug.lib")

#else
#pragma comment(lib, "../../../SoundLib/Lib/SoundLibRelease.lib")
#endif // _DEBUG

#include "../../../SoundLib/Include/SoundsManager.h"
#include "../../../SoundLib/Include/SoundLibCWrapper.h"

#include "../../../GameLib/ObjectManager/Object2DBase.h"
#include "../../../GameLib/2DHelper/2DHelper.h"

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

	void Load();

private:
	
	SharedInformation m_sharedInformation;    //!< 共有クラスの実体

	SoundLib::SoundsManager soundsManager;

	std::thread m_loadImageThread;

	int m_catPawframecount;

	int m_catPawRendercount;

	Texture m_texture;

	Texture m_loading;

	Texture m_catPaw;

	Simple2DVertex m_vertices[4];

	Simple2DVertex m_loadingvertices[4];

	struct CustomVertices
	{
		Simple2DVertex vertex[4];
	};

	CustomVertices m_catPawvertices[8];
	
	bool m_loadIsFinished = false;
};
