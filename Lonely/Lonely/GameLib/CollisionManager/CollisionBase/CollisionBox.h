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
	* @param XYZ方向の長さ
	*/
	CollisionBox(Object* owner, int type, D3DXVECTOR3* length);

	/**
	* @brief 指定軸番号の方向ベクトルを取得
	* @param X,Y,Zのどの軸か
	*/
	D3DXVECTOR3 GetDirect(int elem);
									   
    /**
	* @brief 指定軸方向の長さを取得
	* @param X,Y,Zのどの軸か
	*/
	FLOAT       GetLength(int elem);  

	/**
	* @brief このCollisionBoxを持つオーナーのポジションを取得する
	*/
	D3DXVECTOR3 GetPosition();       

	/**
	* @brief このCollisionBoxを持つオーナーの縦移動させていないポジションを取得する関数
	*/
	D3DXVECTOR3 GetFollowingPositionExceptY();

protected:

	FLOAT       m_length[3];           //!< 各軸方向の長さ
	D3DXVECTOR3 m_position;            //!< 位置
	D3DXVECTOR3 m_normaDirect[3];      //!< 方向ベクトル

};
