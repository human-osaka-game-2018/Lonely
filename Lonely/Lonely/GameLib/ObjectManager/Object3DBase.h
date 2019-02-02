/**
* @file Object3DBase.h
* @brief Object3DBaseクラスのヘッダファイル
* @author shion-sagawa
*/
#pragma once

#include <d3dx9math.h>

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

	D3DXVECTOR3 GetPosition() { return m_position; }

	D3DXVECTOR3 GetFollowingPositionExceptY() { return m_followingPositionExceptY; };

protected:

	bool        m_canRender = true;            //!< 描画できるかどうか
	D3DXVECTOR3 m_position;                    //!< 位置
	D3DXVECTOR3 m_followingPositionExceptY;    //!< Y以外,移動させた後の位置
};
