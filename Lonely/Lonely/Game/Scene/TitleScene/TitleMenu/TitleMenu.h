/**
* @file TitleMenu.h
* @brief TitleMenu�N���X�̃w�b�_�t�@�C��
* @author shion-sagawa
*/

#pragma once

#include "../../../../GameLib/ObjectManager/Object.h"
#include "../../../../GameLib/DirectX/DirectX.h"
#include "../../../../GameLib/2DHelper/2DHelper.h"
#include "../../../../GameLib/FBX/VertexBuffer.h"
#include "../../../../GameLib/FBX/Texture.h"
#include "MenuPressEnter.h"
#include "MenuGameStart.h"
#include "MenuGameEnd.h"
#include "MenuCursor.h"


//#ifdef  _DEBUG
//#pragma comment(lib, "../../../SoundLib/Lib/SoundLibDebug.lib")
//
//#else
//#pragma comment(lib, "../../../SoundLib/Lib/SoundLibRelease.lib")
//#endif // _DEBUG

#include "../../../../SoundLib/Include/SoundsManager.h"
#include "../../../../SoundLib/Include/SoundLibCWrapper.h"


/**
* @brief �^�C�g�����j���[�̑���菇
*/
enum TITLEMENU_STEP
{
	STEP1,      //!< �G���^�[���������܂ł̃X�e�b�v
	STEP2,      //!< �J�[�\�����Q�[���X�^�[�g�ɂ���X�e�b�v
	STEP3       //!< �J�[�\�����Q�[���G���h�ɂ���X�e�b�v
};


/**
* @brief �^�C�g�����j���[�̏������܂Ƃ߂��N���X
*/
class TitleMenu : public Object
{
public:

	TitleMenu();
	~TitleMenu();

	/**
	* @brief ����������֐�
	* @param
	*/
	bool Initialize();

	/**
	* @brief �������֐�
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

	MenuPressEnter m_menuPressEnter;
	MenuGameStart  m_menuGameStart;
	MenuGameEnd    m_menuGameEnd;
	MenuCursor     m_menuCursor;

	int            m_step = STEP1;

	SoundLib::SoundsManager soundsManager;

};
