
#include "DataSelectScene.h"
#include "Object/Data1.h"
#include "Object/Data2.h"
#include "Object/Data3.h"

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
	m_pObjectManager->RegisterObject(new Data1);
	m_pObjectManager->RegisterObject(new Data2);
	m_pObjectManager->RegisterObject(new Data3);

	return true;
}

void DataSelectScene::Finalize()
{
	m_pObjectManager->ReleaseObject();
}

void DataSelectScene::Update()
{
	//このシーンのオブジェクトの更新を行う
	m_pObjectManager->Update();
}

void DataSelectScene::Render()
{
	//オブジェクトのRender
	m_pObjectManager->Render();
}