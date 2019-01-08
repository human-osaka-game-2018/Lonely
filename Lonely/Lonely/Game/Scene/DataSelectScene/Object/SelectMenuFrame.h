/**
* @file SelectMenuFrame.h
* @brief SelectMenuFrame�N���X�̃w�b�_�t�@�C��
* @author shion-sagawa
*/

#pragma once

#include "../../../../GameLib/ObjectManager/Object2DBase.h"
#include "../../../../GameLib/DirectX/DirectX.h"
#include "../SelectCursorInformation/SelectCursorInformation.h"

/**
* @brief �Z���N�g���j���[�̏������܂Ƃ߂��N���X
*/
class SelectMenuFrame : public Object2DBase
{
public:

	SelectMenuFrame();
	~SelectMenuFrame();

	explicit SelectMenuFrame(SelectCursorInformation* instance);

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
	Simple2DVertex           m_verticesBackFrame[4];

};


