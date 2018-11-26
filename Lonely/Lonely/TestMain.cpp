#include ""
#include "Scene/SystemScene.h"


// �G���g���[�|�C���g
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// DirectXLib�̏�����
	DirectXLib::Instance.Initialize("DirectXLib", 1280, 720, false);

	// �V�X�e���V�[���֑J�ڂ���
	SCENEMANAGER->JumpScene(new SystemScene);

	DirectXLib::Instance.MainLoop();

	// DirectXLib�̉��
	DirectXLib::Instance.Finalize();

	return 0;
}
