/**
* @file ObjectManager.h
* @brief ObjectManagerクラスのヘッダファイル
* @author 佐川
*/

#pragma once
#include "Object.h"

/**
* オブジェクトを管理するクラス
*/
class ObjectManager
{
public:

	///**
	//* @brief インスタンスを生成する関数
	//*/
	//static ObjectManager* GetInstance();

	///**
	//* @brief インスタンスを破棄する関数
	//*/
	//static void ReleaseInstance();

	ObjectManager();
	~ObjectManager();

	/**
	* @brief インスタンスを生成する関数
	*/
	void Initialize();

	/**
	* @brief インスタンスを破棄する関数
	*/
	void Finalize();
	
	/**
	* @brief オブジェクトを登録する関数
	* @param 登録したい派生クラスのポインタ
	*/
	void ResisterObject(Object*);

	/**
	* @brief オブジェクトを解放する関数
	*/
	void ReleaseObject();

	/**
	* @brief 操作関数
	*/
	void Update();

	/**
	* @brief 描画関数
	*/
	void Render();
	
private:

	static std::vector<Object*> m_pObjectVec;				//!< Objectクラスの
	//static ObjectManager* m_pObjectManager;					//!< ObjectManagerクラスのインスタンスへのポインタ変数
};
