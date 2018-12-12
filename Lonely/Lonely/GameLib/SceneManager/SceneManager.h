/**
* @file SceneManager.h
* @brief SceneManager�N���X�̃w�b�_�t�@�C��
* @author shion-sagawa
*/

#pragma once

//#include "..\GameLib.h"
#include "SceneBase\SceneBase.h"

/**
* �V�[�����Ǘ�����N���X
*/
class SceneManager
{
public:
	SceneManager(void);
	~SceneManager(void);

	/**���������s���֐�*/
	void Initialize(void);
	/**������s���֐�*/
	void Finalize(void);
	/**����̍X�V���s���֐�*/
	void Update(void);
	/**�`����s���֐�*/
	void Render(void);

	/**�V�[���̑J�ڂ��s���֐�*/
	bool ChangeScene(SceneBase* pScene);
	
private:

	SceneBase* m_pScene;											   
};

//���o�[�W�����̃V�[���}�l�[�W���A�߂���������Ȃ�����u���Ă���
//enum SCENE_STATE
//{
//	INIT,
//	MAIN,
//	RELEASE
//};
//
//class SceneManager
//{
//public:
//	///**�C���X�^���X�𐶐�����֐�*/
//	//static SceneManager* GetInstance();
//	///**�C���X�^���X��j������֐�*/
//	//void ReleaseInstance();
//	/**����������֐�*/
//	void Initialize(void);
//	/**�Q�[���̏������܂Ƃ߂Ď��s����֐�*/
//	void DevideSceneOperation();
//
//private:
//	/**�R���X�g���N�^*/
//	SceneManager();
//	/**�f�X�g���N�^*/
//	~SceneManager();
//	/**�V�[����؂�ւ���֐�*/
//	void ChangeScene();
//	/**����֐�*/
//	void Update();
//	/**�`��֐�*/
//	void Render();
//
//	static SceneManager*  m_pSceneManager;             //!< SceneManager�N���X�̃C���X�^���X�ւ̃|�C���^�ϐ�
//	SceneBase* m_pScene = nullptr;					   //!< Scene�N���X�̃C���X�^���X�ւ̃|�C���^�ϐ�
//	int m_currentScene = TITLE_SCENE;				   //!< ���ǂ̃V�[���Ȃ̂���ۑ�����
//	int m_nextScene = DATA_SELECT_SCENE;			   //!< ���ǂ̃V�[���Ȃ̂���ۑ�����
//	int m_sceneState = INIT;						   //!< �V�[�����ǂ�ȏ�ԂȂ̂���ۑ�����
//	
//	
//};

//SceneManager* SceneManager::m_pSceneManager = nullptr;
//
//SceneManager* SceneManager::GetInstance() 
//{
//	if (m_pSceneManager == nullptr) 
//	{ 
//		m_pSceneManager = new SceneManager;						//�V�[���}�l�[�W���̃C���X�^���X�𐶐�����
//	}
//	return m_pSceneManager;
//}
//
//void SceneManager::ReleaseInstance()
//{
//	delete m_pSceneManager;										//�V�[���}�l�[�W���̃C���X�^���X��j������
//	m_pSceneManager = nullptr;
//}
//
//void SceneManager::ChangeScene()
//{
//	if (m_currentScene == m_nextScene)
//	{
//		return;
//	}
//
//	switch (m_nextScene)
//	{
//	case SCENE_ID::TITLE_SCENE:									//�^�C�g���V�[���Ɉڂ�Ƃ�
//
//		delete m_pScene;
//
//		m_currentScene = SCENE_ID::TITLE_SCENE;
//		m_pScene = new TitleScene();
//
//		break;
//	case SCENE_ID::DATA_SELECT_SCENE:							//�f�[�^�Z���N�g�V�[���Ɉڂ�Ƃ�
//
//		delete m_pScene;
//
//		m_currentScene = SCENE_ID::DATA_SELECT_SCENE;
//		m_pScene = new DataSelectScene();
//
//		break;
//	case SCENE_ID::GAME_SCENE:									//�Q�[���V�[���Ɉڂ�Ƃ�
//
//		delete m_pScene;
//
//		m_currentScene = SCENE_ID::GAME_SCENE;
//		m_pScene = new GameScene();
//
//		break;
//	default:
//
//		break;
//	}
//}
//
//void SceneManager::DevideSceneOperation() 
//{
//	switch (m_sceneState)
//	{
//	case INIT:
//		m_pScene->Init();										//�V�[���ł̏�������������
//		break;
//	case MAIN:
//		//m_pScene->UpdateInput
//		m_pScene->Update();										//�Q�[���̑��쏈�����s��
//		m_pScene->Render();										//�Q�[���̕`�揈�����s��
//		break;
//	case RELEASE:
//		m_pScene->Release();									//�V�[���ł̏����������
//		break;
//	}
//
//	m_pScene->UpdateNextScene(&m_nextScene);					//�V�[���̏���V��������
//	ChangeScene();												//�V�[�����؂�ւ���K�v������ΐ؂�ւ���
//}
