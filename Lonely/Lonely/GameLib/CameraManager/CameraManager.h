/**
* @file CameraManager.h
* @brief CameraManagerクラスのヘッダ
* @author shion-sagawa
*/

#pragma once

#include <windows.h>
#include <tchar.h>
#include <map>
#include <d3dx9.h>
#include "CameraBase.h"

/**
* @brief カメラを登録し、それを渡したりするクラス
*/
class CameraManager
{
public:

	CameraManager();
	~CameraManager();

	/**
	* @brierf 初期化を行う関数
	*/
	void Initialize();

	/**
	* @brief 解放を行う関数
	*/
	void Finalize();

	/**
	* @brief 更新を行う関数
	*/
	void Update();

	/**
	* @brief カメラを変更する関数
	* @param 変更したいカメラクラスのアドレス
	*/
	void  ChangeCamera(CameraBase* pCamera);

private:

	CameraBase * m_pCamera;     //!< カメラIDのマップ配列
};
