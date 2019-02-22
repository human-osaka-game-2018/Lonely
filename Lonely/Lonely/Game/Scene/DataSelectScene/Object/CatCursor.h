/**
* @file CatCursor.h
* @brief CatCursor�N���X�̃w�b�_�t�@�C��
* @author shion-sagawa
*/

#pragma once

#include "../../../../GameLib/ObjectManager/Object2DBase.h"
#include "../../../../GameLib/DirectX/DirectX.h"
#include "../SelectCursorInformation/SelectCursorInformation.h"

/**
* @brief �L�^�J�[�\���̏������܂Ƃ߂��N���X
*/
class CatCursor : public Object2DBase
{
public:

	CatCursor();
	~CatCursor();

	explicit CatCursor(SelectCursorInformation* instance);

	/**
	* @brief ����������֐�
	* @return ����������肭�ł��Ă��Ȃ���FALSE
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

	SelectCursorInformation* m_pSelectCursorInformation;

};
