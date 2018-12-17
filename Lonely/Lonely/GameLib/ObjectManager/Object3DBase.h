/**
* @file Object3DBase.h
* @brief Object3DBaseクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include "Object.h"

/**
* @brief 3Dオブジェクトの基底となるクラス
*/
class Object3DBase : public Object
{
public:

	Object3DBase();
	virtual ~Object3DBase();

	/**
	* @brief 初期化を行う関数
	*/
	virtual bool Initialize();

	/**
	* @brief 解放を行う関数
	*/
	virtual void Finalize();

	/**
	* @brief 操作の更新を行う関数
	*/
	virtual void Update();

	/**
	* @brief 描画を行う関数
	*/
	virtual void Render();

protected:

	bool m_canRender = true;         //!<　描画できるかどうか
};
