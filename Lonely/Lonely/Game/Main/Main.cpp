/**
* @file Main.cpp
* @brief �G���g���[�֐��̃\�[�X�t�@�C��
* @author shion-sagawa
*/

#include "../../GameLib/GameLib.h"
#include "../Scene/TitleScene/TitleScene.h"

// �G���g���[�|�C���g
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// GameLib�̏�����
	GameLib::Instance.Initialize(L"Lonely", 1280, 720, false);

	// �V�X�e���V�[���֑J�ڂ���
	SCENEMANAGER->ChangeScene(new TitleScene);

	GameLib::Instance.MainLoop();

	// DirectXLib�̉��
	GameLib::Instance.Finalize();

	return 0;
}
