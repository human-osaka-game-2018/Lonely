/**
* @file Sumahoneko.cpp
* @brief Sumahoneko�N���X�̃\�[�X�t�@�C��
* @author shion-sagawa
*/

#include "Sumahoneko.h"
#include "../../../GameLib/GameLib.h"

#define _CRT_SECURE_NO_WARNINGS

Sumahoneko::Sumahoneko()
	: m_pSharedInformation(SharedInformation::Instance.GetSharedInformation())
{
	Initialize();
}

Sumahoneko::~Sumahoneko()
{
	Finalize();
}

//����������
bool Sumahoneko::Initialize()
{
	m_fbxStage.Load("../Graphics/stage2_1.fbx");
	m_fbxModel.Load("../Graphics/sumahoneko.fbx");
	m_shpere.CreateShpere(32);

	m_position = { 0.f, 0.f, 0.f };
	m_playerRadius = 0.1f;
	m_playerSpeed = 0.1f;
	m_playerDirection = 0.0f;
	return true;
}

//�������
void Sumahoneko::Finalize()
{
	m_fbxModel.Finalize();
	m_fbxStage.Finalize();
	m_shpere.Finalize();
}

//�X�V����
void Sumahoneko::Update()
{
	//�X�s�[�h�����߂�
	float transSpeed = 0.1f;

	//�J�����̈ʒu���擾����
	D3DXVECTOR3 cameraPosition = m_pSharedInformation->GetCameraPosition();
	//�J�����̕����x�N�g�������߂�
	D3DXVECTOR3 vecCameraDirection(m_position.x - cameraPosition.x, m_position.y -cameraPosition.y, m_position.z - cameraPosition.z);

	//�x�N�g���̑傫����ۑ�����
	float vecSize;
	vecSize = powf((vecCameraDirection.x * vecCameraDirection.x) + (vecCameraDirection.y * vecCameraDirection.y) + (vecCameraDirection.z*vecCameraDirection.z), 0.5);

	//�P�ʃx�N�g�����o���Ă���A�X�s�[�h���|���āA�ړ��ʂ��v�Z����
	D3DXVECTOR3 movementSpeed = {0.f,0.f,0.f};
	movementSpeed.x = (vecCameraDirection.x / vecSize) * transSpeed;
	movementSpeed.z = (vecCameraDirection.z / vecSize) * transSpeed;

	//���̃t���[���ňړ������
	D3DXVECTOR3 movementThisFrame = { 0.f,0.f,0.f };
	
	//�L�[���͂ňړ�
	if (DIRECT_INPUT->KeyboardIsHeld(DIK_W))
	{
		//�ړ��ʂ�ۑ�
		movementThisFrame.x += movementSpeed.x;
		movementThisFrame.z += movementSpeed.z;
		
		//�L�����̌�����ς���
		m_playerDirection = m_pSharedInformation->GetCameraDirection();

	}
	if (DIRECT_INPUT->KeyboardIsHeld(DIK_S))
	{
		movementThisFrame.x -= movementSpeed.x;
		movementThisFrame.z -= movementSpeed.z;
		
		m_playerDirection = m_pSharedInformation->GetCameraDirection() + 3.14;
	}
	if (DIRECT_INPUT->KeyboardIsHeld(DIK_A))
	{
		movementThisFrame.x -= movementSpeed.z;
		movementThisFrame.z += movementSpeed.x;
		
		m_playerDirection = m_pSharedInformation->GetCameraDirection() - 1.57;
	}
	if (DIRECT_INPUT->KeyboardIsHeld(DIK_D))
	{
		movementThisFrame.x += movementSpeed.z;
		movementThisFrame.z -= movementSpeed.x;
		
		m_playerDirection = m_pSharedInformation->GetCameraDirection() + 1.57;
	}
	if (DIRECT_INPUT->KeyboardIsHeld(DIK_F))
	{
		movementThisFrame.y += movementSpeed.y;
	}

	//�X�}�z�L���ړ�������
	m_position.x += movementThisFrame.x;
	m_position.y += movementThisFrame.y;
	m_position.z += movementThisFrame.z;

	//����hitDist�̓��C�̋����̐���
	float hitDist = 3.0f;
	D3DXVECTOR3 hitPos(m_position);
	// ������ɓ����蔻����Ƃ�ꍇ�͏����ォ�画�肷��
	m_position.y += 1.0f;
	hitPos.y += 1.0f;
	const float tyousei = 0.5f;
	// �n�ʂƂ̓����蔻��(�v���C���[�̈ʒu����^���ɓ����蔻����s��)
	if (m_fbxStage.RayPick(&m_position, &D3DXVECTOR3(0.0f, -1.0f, 0.0f), &hitDist, &hitPos) != -1)
	{
		// ���������ꍇ�̓v���C���[�̍�����n�ʂɐݒu������
		m_position.y = hitPos.y + m_playerRadius;
	}
	else
	{
		m_position.y -= 1.0f;
	}


	{
		//����hitDist�̓��C�̋����̐���
		float hitDist2 = fabs(movementThisFrame.x);
		D3DXVECTOR3 hitPos2(m_position);
		// ������ɓ����蔻����Ƃ�ꍇ�͏����ォ�画�肷��
		m_position.y += 2.0f;
		hitPos2.y += 2.0f;
		// �n�ʂƂ̓����蔻��(�v���C���[�̈ʒu����^���ɓ����蔻����s��)
		if (m_fbxStage.RayPick(&m_position, &D3DXVECTOR3(movementThisFrame.x, 0.0f, 0.0f), &hitDist2, &hitPos2) != -1)
		{
			if (movementThisFrame.x > 0) 
			{
				//�����蔻��ł��ꂽ�������ۑ�����
				movementThisFrame.x += (hitPos2.x - tyousei) - m_position.x;
				// ���������ꍇ�̓v���C���[�̍�����n�ʂɐݒu������
				m_position.x = hitPos2.x - tyousei;
			}
			else if (movementThisFrame.x <= 0)
			{
				//�����蔻��ł��ꂽ�������ۑ�����
				movementThisFrame.x += (hitPos2.x + tyousei) - m_position.x;
				m_position.x = hitPos2.x + tyousei;
			}
			m_position.y -= 2.0f;
		}
		else
		{
			m_position.y -= 2.0f;
		}
	}
	{
		float hitDist2 = fabs(movementThisFrame.x);
		D3DXVECTOR3 hitPos2(m_position);
		// ������ɓ����蔻����Ƃ�ꍇ�͏����ォ�画�肷��
		m_position.y += 0.5f;
		hitPos2.y += 0.5f;
		// �n�ʂƂ̓����蔻��(�v���C���[�̈ʒu����^���ɓ����蔻����s��)
		if (m_fbxStage.RayPick(&m_position, &D3DXVECTOR3(movementThisFrame.x, 0.0f, 0.0f), &hitDist2, &hitPos2) != -1)
		{
			if (movementThisFrame.x > 0) 
			{
				//�����蔻��ł��ꂽ�������ۑ�����
				movementThisFrame.x += (hitPos2.x - tyousei) - m_position.x;
				// ���������ꍇ�̓v���C���[�̍�����n�ʂɐݒu������
				m_position.x = hitPos2.x - tyousei;
			}
			else if (movementThisFrame.x <= 0)
			{
				//�����蔻��ł��ꂽ�������ۑ�����
				movementThisFrame.x += (hitPos2.x + tyousei) - m_position.x;
				m_position.x = hitPos2.x + tyousei;
			}
			m_position.y -= 0.5f;
		}
		else
		{
			m_position.y -= 0.5f;
		}
	}

	{
		//����hitDist�̓��C�̋����̐���
		float hitDist2 = fabs(movementThisFrame.z);
		D3DXVECTOR3 hitPos2(m_position);
		// ������ɓ����蔻����Ƃ�ꍇ�͏����ォ�画�肷��
		m_position.y += 2.0f;
		hitPos2.y += 2.0f;
		// �n�ʂƂ̓����蔻��(�v���C���[�̈ʒu����^���ɓ����蔻����s��)
		if (m_fbxStage.RayPick(&m_position, &D3DXVECTOR3(0.f, 0.0f, movementThisFrame.z), &hitDist2, &hitPos2) != -1)
		{
			if (movementThisFrame.z > 0) {
				//�����蔻��ł��ꂽ�������ۑ�����
				movementThisFrame.z +=(hitPos2.z - tyousei) -  m_position.z;
				// ���������ꍇ�̓v���C���[�̍�����n�ʂɐݒu������
				m_position.z = hitPos2.z - tyousei;
			}
			else if (movementThisFrame.z <= 0)
			{
				//�����蔻��ł��ꂽ�������ۑ�����
				movementThisFrame.z += (hitPos2.z + tyousei) - m_position.z;

				m_position.z = hitPos2.z + tyousei;
			}
			m_position.y -= 2.0f;
		}
		else
		{
			m_position.y -= 2.0f;
		}
	}

	{
		float hitDist2 = fabs(movementThisFrame.z);
		D3DXVECTOR3 hitPos2(m_position);
		// ������ɓ����蔻����Ƃ�ꍇ�͏����ォ�画�肷��
		m_position.y += 0.5f;
		hitPos2.y += 0.5f;
		// �n�ʂƂ̓����蔻��(�v���C���[�̈ʒu����^���ɓ����蔻����s��)
		if (m_fbxStage.RayPick(&m_position, &D3DXVECTOR3(0.f, 0.0f, movementThisFrame.z), &hitDist2, &hitPos2) != -1)
		{
			if (movementThisFrame.z > 0) 
			{
				//�����蔻��ł��ꂽ�������ۑ�����
				movementThisFrame.z += (hitPos2.z - tyousei) - m_position.z;

				// ���������ꍇ�̓v���C���[�̍�����n�ʂɐݒu������
				m_position.z = hitPos2.z - tyousei;
			}
			else if (movementThisFrame.z <= 0)
			{
				//�����蔻��ł��ꂽ�������ۑ�����
				movementThisFrame.z += (hitPos2.z + tyousei) - m_position.z;

				m_position.z = hitPos2.z + tyousei;
			}
			m_position.y -= 0.5f;
		}
		else
		{
			m_position.y -= 0.5f;
		}
	}

	//�ǂƂ̓����蔻����ǂ��ɂ��ł��Ȃ�������
	//hitDist = 1.0;
	//D3DXVECTOR3 hitPos2(m_position);
	//D3DXVECTOR3 sabun;
	//hitPos2.y += 1.0f;
	//hitPos2.z += 0.0f;

	//// �n�ʂƂ̓����蔻��(�v���C���[�̈ʒu����^���ɓ����蔻����s��)
	//if (m_fbxStage.RayPick(&hitPos2, &D3DXVECTOR3(movementThisFrame.x, 0.0f, movementThisFrame.z), &hitDist, &hitPos2) != -1)//�P�ʃx�N�g������Ȃ���
	//{
	//	// ���������ꍇ�̓v���C���[�̈ʒu��ǂɐݒu������
	//	sabun.x = (m_position.x - (hitPos2.x + m_playerRadius));
	//	sabun.z = (m_position.z - (hitPos2.z + m_playerRadius));
	//	movementThisFrame.x += sabun.x;
	//	movementThisFrame.z += sabun.z;

	//	m_position.x = hitPos2.x + m_playerRadius;
	//	m_position.z = hitPos2.x + m_playerRadius;
	//}
	

	//���L�N���X�̒l�̍X�V
	m_pSharedInformation->SetPlayerPosition(m_position);
	m_pSharedInformation->SetPlayerMovement(movementThisFrame);

	
	// ���f���̍s����Z�o
	D3DXMATRIX rot, trans, scale;
	D3DXMatrixScaling(&scale, m_playerRadius, m_playerRadius, m_playerRadius);
	D3DXMatrixRotationY(&rot,/* D3DXToRadian*/(m_playerDirection));
	D3DXMatrixTranslation(&trans, m_position.x, m_position.y, m_position.z);
	D3DXMatrixMultiply(m_shpere.GetWorld(), &scale, &rot);
	D3DXMatrixMultiply(m_shpere.GetWorld(), m_shpere.GetWorld(), &trans);

	*m_fbxModel.GetWorld() = *m_shpere.GetWorld();

}

//�`�悷��
void Sumahoneko::Render()
{
	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();
	DirectX* pDirectX = GameLib::Instance.GetDirectX();

	// �ʏ폑�����݃��[�h�ɐݒ�
	pDirectX->SetRenderMode(DirectX::Normal, false);

	// Z�e�X�g�̔�r���@
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// ���f���̕`��
	m_fbxModel.Render();
	m_fbxStage.Render();

	/*char s[50];
	sprintf_s(s,50,"position.x %f", m_position.x);
	DEBUGFONT->DrawText(50, 50, 0xffffffff, s);
*/
}
