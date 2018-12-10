/**
* @file TestCamera.h
* @brief TestCameraクラスのヘッダファイル
* @author 佐川
*/

#pragma once

#include <d3dx9math.h>
#include "../../../../GameLib/CameraManager/CameraBase.h"

/**
* @brief ゲームシーンのクラス
*/
class TestCamera : public CameraBase
{
public:

	TestCamera();
	~TestCamera();

	/**
	* @brief 初期化関数
	*/
	void Initialize();

	/**
	* @brief 解放関数
	*/
	void Finalize();

	/**
	* @brief 操作関数
	*/
	void Update();

private:



	D3DXMATRIXA16 m_matProjection;    //!< プロジェクション行列
	float m_perspective;              //!< カメラの視野角を変えるための変数
	D3DXVECTOR3 m_position;           //!< カメラの位置
	D3DXVECTOR3 m_lookAt;             //!< 注視点の位置
	D3DXVECTOR3 m_rotation;           //!< カメラの回転角度
};
