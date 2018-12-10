/**
* @file CameraBase.h
* @brief CameraBaseクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

/**
* @brief カメラの基底クラス
*/
class CameraBase
{
public:

	CameraBase();
	virtual~CameraBase();

	/**
	* @brief 初期化を行う関数
	*/
	virtual void Initialize();

	/**
	* @brief 解放を行う関数
	*/
	virtual void Finalize();

	/**
	* @brief 操作関数
	*/
	virtual void Update();

protected:

};
