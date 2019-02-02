/**
* @file CollisionBox.h
* @brief CollisionBoxクラスのヘッダファイル
* @author shion-sagawa
*/
#pragma once

#include <d3dx9.h>

#include "CollisionBase.h"

/**
* @brief ボックスの当たり判定クラス
*/
class CollisionBox : public CollisionBase
{
public:
	
	CollisionBox() = delete;
	~CollisionBox();

	/**
	* @brief オーナーが３Dオブジェクトの場合のコンストラクタ
	* @param オーナーのアドレス
	* @param どの当たり判定グループに属するか
	*/
	CollisionBox(Object* owner, int type);

	/**
	* @brief オーナーが３Dオブジェクトの場合のコンストラクタ
	* @param オーナーのアドレス
	* @param どの当たり判定グループに属するか
	* @param 当たり判定の中心位置
	* @param XYZ方向の長さ
	*/
	CollisionBox(Object* owner, int type, D3DXVECTOR3* length);

	// 指定軸番号の方向ベクトルを取得
	D3DXVECTOR3 GetDirect(int elem);
									   
    // 指定軸方向の長さを取得
	FLOAT       GetLength(int elem);  

	D3DXVECTOR3 GetPosition();       

	D3DXVECTOR3 GetFollowingPositionExceptY();

protected:

	FLOAT       m_length[3];           //!< 各軸方向の長さ
	D3DXVECTOR3 m_position;            //!< 位置
	D3DXVECTOR3 m_normaDirect[3];      //!< 方向ベクトル

};
