/**
* @file GameScene.h
* @brief GameScene�N���X�̃w�b�_�t�@�C��
* @author shion-sagawa
*/

#pragma once

#include "../../../GameLib/SceneManager/SceneBase/SceneBase.h"
#include "SharedInformation/SharedInformation.h"


#ifdef  _DEBUG
#pragma comment(lib, "../../../SoundLib/Lib/SoundLibDebug.lib")

#else
#pragma comment(lib, "../../../SoundLib/Lib/SoundLibRelease.lib")
#endif // _DEBUG

#include "../../../SoundLib/Include/SoundsManager.h"
#include "../../../SoundLib/Include/SoundLibCWrapper.h"


/**
* @brief �Q�[���V�[���̃N���X
*/
class GameScene : public SceneBase
{
public:

	GameScene();
	~GameScene();

	/**
	* @brief �������֐� 
	*/
	bool Initialize();

	/**
	* @brief ����֐�
	*/
	void Finalize();

	/**
	* @brief ����֐�
	*/
	void Update();

	/**
	* @brief �`��֐�
	*/
	void Render();

private:
	
	SharedInformation m_sharedInformation;    //!< ���L�N���X�̎���

	SoundLib::SoundsManager soundsManager;

};
