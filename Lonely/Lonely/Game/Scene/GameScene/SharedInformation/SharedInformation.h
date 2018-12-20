/**
* @file SharedInformation.h
* @brief SharedInformation�N���X�̃w�b�_�t�@�C��
* @author shion-sagawa
*/

#pragma once

#include <d3dx9math.h>

/**
* @brief ���L���������܂Ƃ߂��N���X
*/
class SharedInformation
{
public:

	/**
	* @brief �v���C���[���ǂ̃L�����𓮂����Ă��邩
	*/
	enum PLAYER_INITIATIVE
	{
		SUMAHONEKO,        //!< �X�}�z�L�𑀍삵�Ă���Ƃ�
		DRONE              //!< �h���[���𑀍삵�Ă���Ƃ�
	};

	/**
	* @brief �J�����̃��[�h
	*/
	enum CAMERA_MODE
	{
		DEFAULT_CAMERA,    //!< �ʏ�̃J����
		APULI_CAMERA       //!< �X�}�z�L�̃A�v���̃J����
	};

	SharedInformation();
	~SharedInformation();

	/**
	* @brief �������֐�
	*/
	bool Initialize();

	/**
	* @brief ����֐�
	*/
	void Finalize();

	/**
	* @brief ���L�N���X�̃A�h���X���擾����֐�
	*/
	SharedInformation* GetSharedInformation() { return &Instance; }


public:

	static SharedInformation Instance;    //!< ���L���N���X�̃C���X�^���X


public: //�Z�b�^�[�ƃQ�b�^�[
	
	//�v���C���[�̈ʒu
	void SetPlayerPosition(D3DXVECTOR3 playerPosition) {
		m_playerPosition.x = playerPosition.x;
		m_playerPosition.y = playerPosition.y;
		m_playerPosition.z = playerPosition.z;
	};

	D3DXVECTOR3 GetPlayerPosition() { return m_playerPosition; };

	//�J�����̈ʒu
	void SetCameraPosition(D3DXVECTOR3 cameraPosition) { 
		m_cameraPosition.x = cameraPosition.x;
		m_cameraPosition.y = cameraPosition.y;
		m_cameraPosition.z = cameraPosition.z;
	};

	D3DXVECTOR3 GetCameraPosition() { return m_cameraPosition; };

	//�v���C���[���ړ�������
	void SetPlayerMovement(D3DXVECTOR3 playerMovement) { 
		m_playerMovement.x = playerMovement.x; 
		m_playerMovement.y = playerMovement.y;
		m_playerMovement.z = playerMovement.z;
	};

	D3DXVECTOR3 GetPlayerMovement() { return m_playerMovement; };

	//�J�����̌���
	void SetCameraDirection(float cameraDirection) { m_cameraDirection = cameraDirection; };

	float GetCameraDirection() { return m_cameraDirection; };

	//�J�����̃��[�h
	void SetCameraMode(int cameraMode) { m_cameraMode = cameraMode; };

	int GetCameraMode() { return m_cameraMode; };

	//�������Ă�L�����͒N��
	void SetPlayerInitiative(int playerInitiative) { m_playerInitiative = playerInitiative; };

	int GetPlayerInitiative() { return m_playerInitiative; };




private:

	D3DXVECTOR3 m_playerPosition;     //!< �v���C���[�̈ʒu
	D3DXVECTOR3 m_cameraPosition;     //!< �J�����̈ʒu
	D3DXVECTOR3 m_playerMovement;     //!< �v���C���[���ړ�������
	float       m_cameraDirection;    //!< �J�����̌���
	int         m_cameraMode;         //!< �J�������ǂ̃��[�h��
	int         m_playerInitiative;   //!< �v���C���[�̑���̎哱���͒N�������Ă��邩�@
};
