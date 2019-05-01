/**
* @file SharedInformation.cpp
* @brief SharedInformationクラスのソースファイル
* @author shion-sagawa
*/

#include "SharedInformation.h"

#include "EnumGameState.h"

SharedInformation SharedInformation::Instance;

SharedInformation::SharedInformation()
{
	Initialize();
}

SharedInformation::~SharedInformation()
{
	Finalize();
}

//初期化する
bool SharedInformation::Initialize()
{
	//セーブデータの情報で初期化する
	//m_playerPosition = SaveData->GetPlayerPosition();
	//m_cameraPosition = SaveData->GetPlayerPosition();
	//m_cameraMode = saveData->GetCameraMode();

	m_playerPosition = { 0.f,0.f,0.f };
	m_cameraPosition = { 0.f,0.f,0.f };
	m_cameraDirection = 0.f;
	m_cameraMode = DEFAULT_CAMERA;
	m_playerInitiative = SUMAHONEKO;
	m_gameState = STORY_INTRODUCTION;
	m_hp = 3;

	return true;
}

//解放する
void SharedInformation::Finalize()
{
	//セーブデータの保存
}
