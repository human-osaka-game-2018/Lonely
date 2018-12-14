/**
* @file SceneBase.h
* @brief SceneBase�N���X�̃w�b�_�t�@�C��
* @author shion-sagawa
*/

#pragma once

#include "../../ObjectManager/ObjectManager.h"
#include "../../CameraManager/CameraManager.h"

/**
* �V�[���̊��N���X
*/
class SceneBase
{
public:
	
	SceneBase();
	virtual ~SceneBase();

	/**�������֐�*/
	virtual bool Initialize() = 0;
	/**����֐�*/
	virtual void Finalize() = 0;
	/**����֐�*/
	virtual void Update() = 0;
	/**�`��֐�*/
	virtual void Render() = 0;
protected:
	
	ObjectManager* m_pObjectManager;	    //!< ObjectManager�N���X�̃C���X�^���X�ւ̃|�C���^
	CameraManager* m_pCameraManager;        //!< CameraManager�N���X�̃C���X�^���X�ւ̃|�C���^
};
