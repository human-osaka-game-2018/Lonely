/**
* @file SceneBase.h
* @brief SceneBaseクラスのヘッダファイル
* @author 佐川 嗣苑
*/

#pragma once

#include "../../ObjectManager/ObjectManager.h"

/**
* シーンの基底クラス
*/
class SceneBase
{
public:
	
	SceneBase();
	virtual ~SceneBase();

	/**初期化関数*/
	virtual bool Initialize() = 0;
	/**解放関数*/
	virtual void Finalize() = 0;
	/**操作関数*/
	virtual void Update() = 0;
	/**描画関数*/
	virtual void Render() = 0;
protected:
	
	ObjectManager* m_pObjectManager;	    //!< ObjectManagerクラスのインスタンスへのポインタ
	//Object* m_pObject;					//!< ObjectManagerクラスのインスタンスへのポインタ変数
};