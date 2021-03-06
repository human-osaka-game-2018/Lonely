/**
* @file DataSelectScene.cpp
* @brief DataSelectSceneクラスのソースファイル
* @author shion-sagawa
*/

#include "DataSelectScene.h"
#include "Object/CatCursor.h"
#include "Object/MiniCursor.h"
#include "Object/Data1.h"
#include "Object/Data2.h"
#include "Object/Data3.h"
#include "Object/SelectBackground.h"
#include "Object/SelectMenuFrame.h"

DataSelectScene::DataSelectScene()
{
	Initialize();
}

DataSelectScene::~DataSelectScene()
{
	Finalize();
}

bool DataSelectScene::Initialize()
{
	//オブジェクトをNEWして、オブまねのVectorにつめる
	m_pObjectManager->RegisterObject(new SelectBackground);
	m_pObjectManager->RegisterObject(new CatCursor(&m_selectCursorInformation));
	m_pObjectManager->RegisterObject(new Data1);
	m_pObjectManager->RegisterObject(new Data2);
	m_pObjectManager->RegisterObject(new Data3);
	m_pObjectManager->RegisterObject(new SelectMenuFrame(&m_selectCursorInformation));
	m_pObjectManager->RegisterObject(new MiniCursor(&m_selectCursorInformation));
	
	return true;
}

void DataSelectScene::Finalize()
{
	m_pObjectManager->ReleaseObject();
}

void DataSelectScene::Update()
{
	//このシーンのオブジェクトの更新を行う
	m_selectCursorInformation.Update();
	m_pObjectManager->Update();
}

void DataSelectScene::Render()
{
	//オブジェクトのRender
	m_pObjectManager->Render();
}