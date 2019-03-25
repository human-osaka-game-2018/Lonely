/**
* @file Sumahoneko.cpp
* @brief Sumahoneko�N���X�̃\�[�X�t�@�C��
* @author shion-sagawa
*/

#include "Sumahoneko.h"
#include "../../../../GameLib/GameLib.h"
#include "../SharedInformation/EnumGameState.h"
#include "../../../../GameLib/CollisionManager/CollisionBase/CollisionBox.h"
#include "../../../../GameLib/CollisionManager/EnumCollision/Enum_CollisionType.h"
#include "../../../../GameLib/CollisionManager/EnumCollision/Enum_CollisionShape.h"
#include "../SharedInformation/EnumGameState.h"

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
	m_fbxModel.Load("../Graphics/smartcat.fbx");
	//m_fbxModel.Load("../Graphics/stage131.fbx");
	m_pFbxStage = m_pSharedInformation->GetStageFbx();
	m_shpere.CreateShpere(32);


	m_position = { 0.f, 2.f, 0.f };
	m_followingPositionExceptY = m_position;
	m_prevPosition = m_position;
	m_pCollision = new CollisionBox(this, PLAYER);

	return true;
}

//�������
void Sumahoneko::Finalize()
{
	m_fbxModel.Finalize();
	m_shpere.Finalize();
}

//�X�V����
void Sumahoneko::Update()
{
	if (m_pSharedInformation->GetGameState() == PAUSE)
	{
		return;
	}


	UpdateDamageCount();

	//�X�s�[�h�����߂�
	float transSpeed = 0.1f;
	const float runSpeed = 2.0f;

	//�J�����̈ʒu���擾����
	D3DXVECTOR3 cameraPosition = m_pSharedInformation->GetCameraPosition();
	//�J�����̕����x�N�g�������߂�
	D3DXVECTOR3 vecCameraDirection(m_position.x - cameraPosition.x, m_position.y -cameraPosition.y, m_position.z - cameraPosition.z);

	//�x�N�g���̑傫����ۑ�����
	float vecSize;
	vecSize = powf((vecCameraDirection.x * vecCameraDirection.x) + (vecCameraDirection.z*vecCameraDirection.z), 0.5);

	//�P�ʃx�N�g�����o���Ă���A�X�s�[�h���|���āA�ړ��ʂ��v�Z����
	D3DXVECTOR3 movementSpeed = {0.f,0.f,0.f};
	movementSpeed.x = (vecCameraDirection.x / vecSize) * transSpeed;
	movementSpeed.z = (vecCameraDirection.z / vecSize) * transSpeed;

	//���̃t���[���ňړ������
	D3DXVECTOR3 movementThisFrame = { 0.f,0.f,0.f };

	//�ړ��������s���O�̒l��ۑ����Ă���
	m_prevPosition = m_position;
	m_followingPositionExceptY.y = m_position.y;
	
	//�ړ��ʂ��u�����v�ɂ���
	m_runs = false;
	if (DIRECT_INPUT->KeyboardIsHeld(DIK_RSHIFT))
	{
		//�ړ��ʂ��u����v�ɂ���
		m_runs = true;
	}

	//�L�[���͂ňړ�
	if (DIRECT_INPUT->KeyboardIsHeld(DIK_W))
	{
		//�ړ��ʂ�ۑ�
		movementThisFrame.x += movementSpeed.x;
		movementThisFrame.z += movementSpeed.z;
		if (m_runs == true)
		{
			movementThisFrame.x += movementSpeed.x * runSpeed;
			movementThisFrame.z += movementSpeed.z * runSpeed;
		}
		
		//�L�����̌�����ς���
		m_playerDirection = m_pSharedInformation->GetCameraDirection();

	}
	if (DIRECT_INPUT->KeyboardIsHeld(DIK_S))
	{
		movementThisFrame.x -= movementSpeed.x;
		movementThisFrame.z -= movementSpeed.z;
		if (m_runs == true)
		{
			movementThisFrame.x -= (movementSpeed.x * runSpeed);
			movementThisFrame.z -= (movementSpeed.z * runSpeed);
		}
		
		m_playerDirection = m_pSharedInformation->GetCameraDirection() + 3.14f;
	}
	if (DIRECT_INPUT->KeyboardIsHeld(DIK_A))
	{
		movementThisFrame.x -= movementSpeed.z;
		movementThisFrame.z += movementSpeed.x;
		if (m_runs == true)
		{
			movementThisFrame.x -= (movementSpeed.z * runSpeed);
			movementThisFrame.z += (movementSpeed.x * runSpeed);
		}
		
		m_playerDirection = m_pSharedInformation->GetCameraDirection() - 1.57f;
	}
	if (DIRECT_INPUT->KeyboardIsHeld(DIK_D))
	{
		movementThisFrame.x += movementSpeed.z;
		movementThisFrame.z -= movementSpeed.x;
		if (m_runs == true)
		{
			movementThisFrame.x += (movementSpeed.z * runSpeed);
			movementThisFrame.z -= (movementSpeed.x * runSpeed);
		}
		
		m_playerDirection = m_pSharedInformation->GetCameraDirection() + 1.57f;
	}

	//�����鏈��
	Fall();
	//�W�����v����
	Jump();
	//�Q�[���I�[�o�[�̃A�j���[�V��������
	AnimateDead();
	//�����蔻���o�^����
	m_pCollisionManager->RegisterCollision(m_pCollision);

	////�X�e�[�W�Ƃ̓����蔻��
	this->DetectUpCollidingWithStage(&movementThisFrame);
	this->DetectDownCollidingWithStage(&movementThisFrame);
	//this->DetectXCollidingWithStage(&movementThisFrame);
	//this->DetectZCollidingWithStage(&movementThisFrame);

	////����hitDist�̓��C�̋����̐���
	//float hitDist = 10.0f;
	//D3DXVECTOR3 hitPos(m_position);
	//// ������ɓ����蔻����Ƃ�ꍇ�͏����ォ�画�肷��
	//m_position.y += 1.0f;
	//hitPos.y += 1.0f;
	//// �n�ʂƂ̓����蔻��(�v���C���[�̈ʒu����^���ɓ����蔻����s��)
	//if (m_pFbxStage->RayPick(&m_position, &D3DXVECTOR3(0.0f, -1.0f, 0.0f), &hitDist, &hitPos) != -1)
	//{
	//	// ���������ꍇ�̓v���C���[�̍�����n�ʂɐݒu������
	//	m_position.y = hitPos.y + m_radius;
	//}
	//else
	//{
	//	m_position.y -= 1.0f;
	//}

	const float tyousei = 0.5f;
	{
		//����hitDist�̓��C�̋����̐���
		float hitDist2 = fabs(movementThisFrame.x);
		D3DXVECTOR3 hitPos2(m_position);
		// ������ɓ����蔻����Ƃ�ꍇ�͏����ォ�画�肷��
		m_position.y += 2.0f;
		hitPos2.y += 2.0f;
		// �n�ʂƂ̓����蔻��(�v���C���[�̈ʒu����^���ɓ����蔻����s��)
		if (m_pFbxStage->RayPick(&m_position, &D3DXVECTOR3(movementThisFrame.x, 0.0f, 0.0f), &hitDist2, &hitPos2) != -1)
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
		if (m_pFbxStage->RayPick(&m_position, &D3DXVECTOR3(movementThisFrame.x, 0.0f, 0.0f), &hitDist2, &hitPos2) != -1)
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
		if (m_pFbxStage->RayPick(&m_position, &D3DXVECTOR3(0.f, 0.0f, movementThisFrame.z), &hitDist2, &hitPos2) != -1)
		{
			if (movementThisFrame.z > 0) {
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
		if (m_pFbxStage->RayPick(&m_position, &D3DXVECTOR3(0.f, 0.0f, movementThisFrame.z), &hitDist2, &hitPos2) != -1)
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

	//�X�}�z�L���ړ�������
	m_position.x += movementThisFrame.x;
	m_position.y += movementThisFrame.y;
	m_position.z += movementThisFrame.z;

	//XZ������������̈ʒu��ۑ�����AY�͓����Ă��Ȃ��ʒu��ۑ�����
	m_followingPositionExceptY.x = m_position.x;
	m_followingPositionExceptY.z = m_position.z;

	//���L�N���X�̒l�̍X�V
	m_pSharedInformation->SetPlayerPosition(m_position);
	m_pSharedInformation->SetPlayerMovement(movementThisFrame);
	
	// ���f���̍s����Z�o
	D3DXMATRIX rot,rot2, rot3,trans, scale;
	D3DXMatrixScaling(&scale, m_radius, m_radius, m_radius);
	if (m_dead == false)
	{
		D3DXMatrixRotationY(&rot, (m_playerDirection));
	}
	else
	{
		D3DXMatrixRotationX(&rot, (m_rotation.x));
		D3DXMatrixRotationY(&rot2, (m_rotation.y));
		D3DXMatrixMultiply(&rot, &rot, &rot2);
		D3DXMatrixRotationZ(&rot3, (m_rotation.z));
		D3DXMatrixMultiply(&rot, &rot, &rot3);
	}

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
	
	char s[100];
	sprintf_s(s,100,"position.y %f gravity %f time %f", m_position.y, m_gravity, m_jumpingTime);
	DEBUGFONT->DrawText(50, 50, 0xffffffff, s);

	if (m_damaged == true)
	{
		char s[100];
		sprintf_s(s, 100, "damaged");
		DEBUGFONT->DrawText(50, 200, 0xffffffff, s);

	}
}

void Sumahoneko::RevertPositionY()
{
	//Y�����ړ�����O�̈ʒu�ɖ߂�
	m_position.y = m_prevPosition.y;
	//�ړ��ʂ�Y�����[���ɂ���A�J���������ړ����Ă��܂��̂�h������
	D3DXVECTOR3 movement;
	movement = m_pSharedInformation->GetPlayerMovement();
	movement.y = 0.f;
	m_pSharedInformation->SetPlayerMovement(movement);
}

void Sumahoneko::RevertPosition()
{
	//�ړ�����O�̈ʒu�ɖ߂�
	m_position = m_prevPosition;
	m_followingPositionExceptY = m_prevPosition;
	
	//�ړ��ʂ��[���ɂ���A�J���������ړ����Ă��܂��̂�h������
	D3DXVECTOR3 movement = { 0.f,0.f,0.f };
	m_pSharedInformation->SetPlayerMovement(movement);
}

void Sumahoneko::Fall()
{
	//���n���Ă�����d�͂��O�ɂ���
	if (m_isLanded == true)
	{
		m_gravity = -2.f;
		m_jumpingTime = 0;
	}
	else
	{
		++m_jumpingTime;
		//�d�́@ ���@ �o�ߎ��ԁ@�@*�@�@�@�d�͉����x�@   
		m_gravity -= m_jumpingTime * m_accelerationGravity;

		if (m_gravity <= m_maxGravity)
		{
			m_gravity = m_maxGravity;
		}
	}
}

void Sumahoneko::Damaged()
{
	if (m_damaged == false)
	{
		m_damaged = true;
		m_damageCount = 60;
		m_hp -= 1;
		m_pSharedInformation->SetHp(m_hp);

		if (m_hp == 0)
		{
			m_dead = true;
			m_pSharedInformation->SetGameState(DEAD);
		}
	}
}

void Sumahoneko::UpdateDamageCount()
{
	if (m_damaged == true) 
	{
		--m_damageCount;
		if (m_damageCount <= 0)
		{
			m_damaged = false;
		}
	}

}

void Sumahoneko::Jump()
{
	//���n���Ă�����
	if (m_isLanded == true) 
	{
		if (DIRECT_INPUT->KeyboardIsReleased(DIK_SPACE))
		{
			//�d�́@ ���@    �����x
			m_gravity = m_initialVelocity;
			m_isLanded = false;
		}
	}
}

void Sumahoneko::DetectUpCollidingWithStage(D3DXVECTOR3* movementThisFrame)
{
	//�ړ���������̎��̃X�e�[�W�Ƃ̓����蔻��
	D3DXVECTOR3 hitPos(m_position);
	//���C�̒���
	float hitDist = m_gravity;
	// ���C�̎n�_�𓪂̈ʒu�܂ŏグ��
	m_position.y += 2.0f;
	hitPos.y += 2.0f;
	// �V��Ƃ̓����蔻��(�v���C���[�̈ʒu����^��ɓ����蔻����s��)
	if (m_gravity > 0) 
	{
		if (m_pFbxStage->RayPick(&m_position, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), &hitDist, &hitPos) != -1)
		{
			//���C�̏Փ˔���ł��炵���� + �X�}�z�L�̑傫���@��ۑ�����
			movementThisFrame->y -= (hitPos.y - m_position.y) + 2.0f;
			// ���������ꍇ�̓v���C���[�̍�����V��M���M���Ɉړ�������
			m_position.y = hitPos.y;
			//������̏d�͂�ł�����
			m_gravity = 0.f;
		}
		else
		{
			movementThisFrame->y += m_gravity;
			// ���C�̎n�_�̂��߂ɒ��������������Ƃɖ߂�
			m_position.y -= 2.0f;
		}
	}
	else 
	{
		// ���C�̎n�_�̂��߂ɒ��������������Ƃɖ߂�
		m_position.y -= 2.0f;
	}
}

void Sumahoneko::DetectDownCollidingWithStage(D3DXVECTOR3* movementThisFrame)
{
	//�ړ����������̎��̃X�e�[�W�Ƃ̓����蔻��
	D3DXVECTOR3 hitPos(m_position);
	//���C�̒���
	float hitDist = 0.f;
	hitDist -= m_gravity;
	// ���C�̎n�_�����̈ʒu�܂ŏグ��
	m_position.y += 1.0f;
	hitPos.y += 1.0f;
	// �n�ʂƂ̓����蔻��(�v���C���[�̈ʒu����^��ɓ����蔻����s��)
	if (m_gravity < 0) {
		if (m_pFbxStage->RayPick(&m_position, &D3DXVECTOR3(0.0f, -1.0f, 0.0f), &hitDist, &hitPos) != -1)
		{
			//���n�������Ƃ�ۑ�����
			m_isLanded = true;
			// ���������ꍇ�̓v���C���[�̍�����n�ʂ�菭����ɐݒu������
			m_position.y = hitPos.y + 0.1f;
			m_jumpingTime = 0.f;
		}
		else
		{
			if (m_isLanded == true)
			{
				//isLanded��false���Ȃ��ƁA�R���痎�����Ȃ��Ȃ�
				m_isLanded = false;
				m_gravity = 0.f;
			}
			movementThisFrame->y += m_gravity;
			// ���C�̎n�_�̂��߂ɒ��������������Ƃɖ߂�
			m_position.y -= 1.0f;
		}
	}
	else
	{
		// ���C�̎n�_�̂��߂ɒ��������������Ƃɖ߂�
		m_position.y -= 1.0f;
	}
}

void Sumahoneko::DetectXCollidingWithStage(D3DXVECTOR3* movementThisFrame)
{
	//�L�����̓��ӂ肩�烌�C���΂�
	{
		float hitDist2 = fabs(movementThisFrame->x);
		D3DXVECTOR3 hitPos2(m_position);
		const float tyousei = 0.1f;
		
		m_position.y += 2.0f;
		hitPos2.y += 2.0f;
		// �n�ʂƂ̓����蔻��(�v���C���[�̈ʒu����^���ɓ����蔻����s��)
		if (m_pFbxStage->RayPick(&m_position, &D3DXVECTOR3(movementThisFrame->x, 0.0f, 0.0f), &hitDist2, &hitPos2) != -1)
		{
			if (movementThisFrame->x > 0)
			{
				//�����蔻��ł��ꂽ�������ۑ�����
				movementThisFrame->x += (hitPos2.x - tyousei) - m_position.x;
				// ���������ꍇ�̓v���C���[�̍�����n�ʂɐݒu������
				m_position.x = hitPos2.x - tyousei;
			}
			else if (movementThisFrame->x <= 0)
			{
				//�����蔻��ł��ꂽ�������ۑ�����
				movementThisFrame->x += (hitPos2.x + tyousei) - m_position.x;
				m_position.x = hitPos2.x + tyousei;
			}
			m_position.y -= 2.0f;
		}
		else
		{
			m_position.y -= 2.0f;
		}
	}

	//�L�����̍��ӂ肩�烌�C���΂�
	{
		float hitDist2 = fabs(movementThisFrame->x);
		D3DXVECTOR3 hitPos2(m_position);
		const float tyousei = 0.1f;
		
		m_position.y += 0.5f;
		hitPos2.y += 0.5f;
		// �n�ʂƂ̓����蔻��(�v���C���[�̈ʒu����^���ɓ����蔻����s��)
		if (m_pFbxStage->RayPick(&m_position, &D3DXVECTOR3(movementThisFrame->x, 0.0f, 0.0f), &hitDist2, &hitPos2) != -1)
		{
			if (movementThisFrame->x > 0)
			{
				//�����蔻��ł��ꂽ�������ۑ�����
				movementThisFrame->x += (hitPos2.x - tyousei) - m_position.x;
				// ���������ꍇ�̓v���C���[�̍�����n�ʂɐݒu������
				m_position.x = hitPos2.x - tyousei;
			}
			else if (movementThisFrame->x <= 0)
			{
				//�����蔻��ł��ꂽ�������ۑ�����
				movementThisFrame->x += (hitPos2.x + tyousei) - m_position.x;
				m_position.x = hitPos2.x + tyousei;
			}
			m_position.y -= 0.5f;
		}
		else
		{
			m_position.y -= 0.5f;
		}
	}
}

void Sumahoneko::DetectZCollidingWithStage(D3DXVECTOR3* movementThisFrame)
{
	//�L�����̓��ӂ肩�烌�C���΂�
	{
		float hitDist2 = fabs(movementThisFrame->z);
		D3DXVECTOR3 hitPos2(m_position);
		const float tyousei = 0.1f;

		m_position.y += 2.0f;
		hitPos2.y += 2.0f;
		// �n�ʂƂ̓����蔻��(�v���C���[�̈ʒu����Z�����ɓ����蔻����s��)
		if (m_pFbxStage->RayPick(&m_position, &D3DXVECTOR3(0.f, 0.0f, movementThisFrame->z), &hitDist2, &hitPos2) != -1)
		{
			if (movementThisFrame->z > 0) {
				//�����蔻��ł��ꂽ�������ۑ�����
				movementThisFrame->z += (hitPos2.z - tyousei) - m_position.z;
				// ���������ꍇ�̓v���C���[�̍�����n�ʂɐݒu������
				m_position.z = hitPos2.z - tyousei;
			}
			else if (movementThisFrame->z <= 0)
			{
				//�����蔻��ł��ꂽ�������ۑ�����
				movementThisFrame->z += (hitPos2.z + tyousei) - m_position.z;

				m_position.z = hitPos2.z + tyousei;
			}
			m_position.y -= 2.0f;
		}
		else
		{
			m_position.y -= 2.0f;
		}
	}

	//�L�����̓��ӂ肩�烌�C���΂�
	{
		float hitDist2 = fabs(movementThisFrame->z);
		D3DXVECTOR3 hitPos2(m_position);
		const float tyousei = 0.1f;
		
		m_position.y += 0.5f;
		hitPos2.y += 0.5f;
		// �n�ʂƂ̓����蔻��(�v���C���[�̈ʒu����Z�����ɓ����蔻����s��)
		if (m_pFbxStage->RayPick(&m_position, &D3DXVECTOR3(0.f, 0.0f, movementThisFrame->z), &hitDist2, &hitPos2) != -1)
		{
			if (movementThisFrame->z > 0)
			{
				//�����蔻��ł��ꂽ�������ۑ�����
				movementThisFrame->z += (hitPos2.z - tyousei) - m_position.z;

				// ���������ꍇ�̓v���C���[�̍�����n�ʂɐݒu������
				m_position.z = hitPos2.z - tyousei;
			}
			else if (movementThisFrame->z <= 0)
			{
				//�����蔻��ł��ꂽ�������ۑ�����
				movementThisFrame->z += (hitPos2.z + tyousei) - m_position.z;

				m_position.z = hitPos2.z + tyousei;
			}
			m_position.y -= 0.5f;
		}
		else
		{
			m_position.y -= 0.5f;
		}
	}
}

void Sumahoneko::AnimateDead()
{
	if (m_dead == false)
	{
		return;
	}

	if (m_dyingAnimeState == ONE)
	{
		m_radian += 0.1f;
		m_rotation.x = 0.5f * cos(m_radian);
		m_rotation.z = 0.5f * sin(m_radian);
		m_rotation.y = m_playerDirection;

		if (m_radian >= 8.85/*15.8*/)
		{
			//m_radian = 0.f;
			m_dyingAnimeState = TWO;
		}
	}
	if (m_dyingAnimeState == TWO)
	{
		m_radian += 0.1f - m_dyingAnimeCount * 0.001f;
		m_rotation.x = 0.5f * cos(m_radian);
		m_rotation.z = 0.5f * sin(m_radian);
		//m_rotation.z += 0.2f;

		++m_dyingAnimeCount;

		if (m_dyingAnimeCount > 60) 
		{
			m_dyingAnimeState = THREE;
			m_dyingAnimeCount = 0;
		}
	}
	if (m_dyingAnimeState == THREE)
	{
		++m_dyingAnimeCount;
		m_rotation.x -= 0.004f * static_cast<float>(m_dyingAnimeCount);
		if (m_rotation.x <= -1.50)
		{
			m_rotation.z = 0.f;
			m_dyingAnimeState = FOUR;
		}
	}
}
