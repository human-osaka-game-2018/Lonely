/**
* @file SharedInformation.h
* @brief SharedInformationクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include <d3dx9math.h>
#include "../../../../GameLib/FBX/FBX.h"

/**
* @brief 共有したい情報まとめたクラス
*/
class SharedInformation
{
public:

	/**
	* @brief プレイヤーがどのキャラを動かしているか
	*/
	enum PLAYER_INITIATIVE
	{
		SUMAHONEKO,        //!< スマホ猫を操作しているとき
		DRONE              //!< ドローンを操作しているとき
	};

	/**
	* @brief カメラのモード
	*/
	enum CAMERA_MODE
	{
		DEFAULT_CAMERA,    //!< 通常のカメラ
		APP_CAMERA         //!< スマホ猫のアプリのカメラ
	};

	SharedInformation();
	~SharedInformation();

	/**
	* @brief 初期化関数
	*/
	bool Initialize();

	/**
	* @brief 解放関数
	*/
	void Finalize();

	/**
	* @brief 共有クラスのアドレスを取得する関数
	*/
	SharedInformation* GetSharedInformation() { return &Instance; }


public:

	static SharedInformation Instance;    //!< 共有情報クラスのインスタンス


public: //セッターとゲッター
	
	//プレイヤーの位置
	void SetPlayerPosition(D3DXVECTOR3 playerPosition) {
		m_playerPosition.x = playerPosition.x;
		m_playerPosition.y = playerPosition.y;
		m_playerPosition.z = playerPosition.z;
	};

	D3DXVECTOR3 GetPlayerPosition() { return m_playerPosition; };

	//カメラの位置
	void SetCameraPosition(D3DXVECTOR3 cameraPosition) { 
		m_cameraPosition.x = cameraPosition.x;
		m_cameraPosition.y = cameraPosition.y;
		m_cameraPosition.z = cameraPosition.z;
	};

	D3DXVECTOR3 GetCameraPosition() { return m_cameraPosition; };

	//プレイヤーが移動した量
	void SetPlayerMovement(D3DXVECTOR3 playerMovement) { 
		m_playerMovement.x = playerMovement.x; 
		m_playerMovement.y = playerMovement.y;
		m_playerMovement.z = playerMovement.z;
	};

	D3DXVECTOR3 GetPlayerMovement() { return m_playerMovement; };

	//カメラの向き
	void SetCameraDirection(float cameraDirection) { m_cameraDirection = cameraDirection; };

	float GetCameraDirection() { return m_cameraDirection; };

	//カメラのモード
	void SetCameraMode(int cameraMode) { m_cameraMode = cameraMode; };

	int GetCameraMode() { return m_cameraMode; };

	//動かしてるキャラは誰か
	void SetPlayerInitiative(int playerInitiative) { m_playerInitiative = playerInitiative; };

	int GetPlayerInitiative() { return m_playerInitiative; };

	//ビュー逆行列
	void SetInverseView(D3DXMATRIXA16 matInverseView) { m_matInverseView = matInverseView; };

	D3DXMATRIXA16 GetInverseView() { return m_matInverseView; };

	//ポーズ画面フラグ
	void SetGameState(int gameState) { m_gameState = gameState; };

	int GetGameState() { return m_gameState; };

	//ステージのFBXモデル
	void SetStageFbx(FbxModel* pStageFbx) { m_pStageFbx = pStageFbx; };
	FbxModel* GetStageFbx() { return m_pStageFbx; };

	void SetMatView(D3DXMATRIX* matView) { m_matView = matView; };
	D3DXMATRIX* GetMatView() { return m_matView; };

	void SetHp(int hp) { m_hp = hp; }
	int GetHp() { return m_hp; }

private:

	D3DXMATRIXA16 m_matInverseView;    //!< ビュー逆行列
	D3DXVECTOR3   m_playerPosition;    //!< プレイヤーの位置
	D3DXVECTOR3   m_cameraPosition;    //!< カメラの位置
	D3DXVECTOR3   m_playerMovement;    //!< プレイヤーが移動した量
	float         m_cameraDirection;   //!< カメラの向き
	int           m_cameraMode;        //!< カメラがどのモードか
	int           m_playerInitiative;  //!< プレイヤーの操作の主導権は誰が持っているか　
	int           m_gameState;         //!< ゲームが一次停止しているかなどの状態
	FbxModel*     m_pStageFbx;         //!< ステージのFBXのポインタ
	D3DXMATRIX*   m_matView;
	int           m_hp = 3;   
};
