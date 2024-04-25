//*****************************************************
//
// �v���C���[�̏���[player.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "player.h"
#include "renderer.h"
#include "manager.h"
#include "inputkeyboard.h"
#include "inputmouse.h"
#include "inputjoypad.h"
#include "inputManager.h"
#include "debugproc.h"
#include "particle.h"
#include "sound.h"
#include "collision.h"
#include "model.h"
#include "texture.h"
#include "camera.h"
#include "collision.h"
#include "universal.h"
#include "game.h"
#include <stdio.h>
#include "motion.h"
#include "afterimage.h"
#include "effect3D.h"
#include "fade.h"
#include "enemyManager.h"
#include "bullet.h"
#include "animEffect3D.h"
#include "shadow.h"
#include "block.h"
#include "orbit.h"
#include "frame.h"
#include "timer.h"
#include "cameraBehavior.h"
#include "slow.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const char* PARAM_PATH = "data\\TEXT\\player.txt";	// �p�����[�^�[�̃p�X
const float LINE_STOP = 0.3f;	// �����Ă锻��̂������l
const int TIME_AFTERIMAGE = 4;	// �c�����o���p�x
const float BULLET_SPEED = 5.0f;	// �e�����e���x
const float BULLET_SIZE = 3.0f;	// �e�����e�T�C�Y
const CScene::MODE MODE_DEATH = CScene::MODE_GAME;	// ���񂾌�ɑJ�ڂ��郂�[�h
const float TIME_HITSTOP_SLASH = 0.1f;	// �a���̃q�b�g�X�g�b�v����
const float SCALE_HITSTOP_SLASH = 0.1f;	// �a���̃q�b�g�X�g�b�v�^�C���X�P�[��
}

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CPlayer *CPlayer::m_pPlayer = nullptr;	// ���g�̃|�C���^

//=====================================================
// �D�揇�ʂ����߂�R���X�g���N�^
//=====================================================
CPlayer::CPlayer(int nPriority)
{
	ZeroMemory(&m_info, sizeof(CPlayer::SInfo));
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CPlayer::~CPlayer()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CPlayer::Init(void)
{
	// ���̓Ǎ�
	Load();

	// �����ʒu�ɐݒ�
	SetPosition(D3DXVECTOR3(0.0f, -16.0f, 0.0f));

	// �l�̏�����
	m_info.state = STATE_NORMAL;
	m_info.jump = JUMPSTATE_NORMAL;

	if (m_info.pCollisionCube == nullptr)
	{// �����̂̓����蔻��
		m_info.pCollisionCube = CCollisionCube::Create(CCollision::TAG_PLAYER, this);

		D3DXVECTOR3 vtxMax = { 5.0f,20.0f,5.0f };
		D3DXVECTOR3 vtxMin = { -5.0f,0.0f,-5.0f };

		if (m_info.pCollisionCube != nullptr)
		{
			m_info.pCollisionCube->SetVtx(vtxMax, vtxMin);
		}
	}

	if (m_info.pClsnAttack == nullptr)
	{// ���̓����蔻�萶��
		m_info.pClsnAttack = CCollisionSphere::Create(CCollision::TAG_NONE, CCollision::TYPE_SPHERE, this);

		if (m_info.pClsnAttack != nullptr)
		{// ���̐ݒ�
			m_info.pClsnAttack->SetPosition(D3DXVECTOR3(0.0f,0.0f,0.0f));
			m_info.pClsnAttack->SetRadius(0.0f);
		}
	}

	if (m_info.pClsnHit == nullptr)
	{// ��e�����蔻�萶��
		m_info.pClsnHit = CCollisionSphere::Create(CCollision::TAG_PLAYER, CCollision::TYPE_SPHERE, this);

		if (m_info.pClsnHit != nullptr)
		{// ���̐ݒ�
			m_info.pClsnHit->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_info.pClsnHit->SetRadius(1.0f);
		}
	}

	// �����̌����ݒ�
	D3DXVECTOR3 rot = { 0.0f,-D3DX_PI * 0.5f,0.0f };

	m_info.rotDest = rot;
	SetRot(rot);

	// �o�����[�V�����̐ݒ�
	CGame *pGame = CGame::GetInstance();
	int nProgress = 0;

	if (pGame != nullptr)
	{
		nProgress = pGame->GetProgress();
	}

	//if (nProgress == 0)
	//{
	//	SetMotion(MOTION_APPER);

	//	// �^�C�}�[���~�߂�
	//	CTimer *pTimer = CTimer::GetInstance();

	//	if (pTimer != nullptr)
	//	{
	//		pTimer->EnableStop(true);
	//	}

	//	// �t���[�����o�̐���
	//	CFrame::Create(20, 120, 70);

	//	// �J���������̐ݒ�
	//	CCamera *pCamera = CManager::GetCamera();

	//	if (pCamera != nullptr)
	//	{
	//		pCamera->SetDist(100.0f);

	//		pCamera->ChangeBehavior(new CCameraBehaviorApperPlayer);
	//	}
	//}
	//else
	{
		// �J�����ɒǏ]�r�w�C�r�A��ݒ�
		CCamera *pCamera = CManager::GetCamera();

		if (pCamera != nullptr)
		{
			pCamera->ChangeBehavior(new CCameraBehaviorFollowPlayer);
		}
	}

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CPlayer::Uninit(void)
{
	if (m_info.pBody != nullptr)
	{// �̂̔j��
		m_info.pBody->Uninit();
		m_info.pBody = nullptr;
	}

	if (m_info.pCollisionCube != nullptr)
	{// �����蔻��j��
		m_info.pCollisionCube->Uninit();
		m_info.pCollisionCube = nullptr;
	}

	if (m_info.pClsnAttack != nullptr)
	{// �U�������蔻��j��
		m_info.pClsnAttack->Uninit();
		m_info.pClsnAttack = nullptr;
	}

	if (m_info.pClsnHit != nullptr)
	{// ��e�����蔻��j��
		m_info.pClsnHit->Uninit();
		m_info.pClsnHit = nullptr;
	}

	if (m_pPlayer != nullptr)
	{// ���g�̃|�C���^����ɂ���
		m_pPlayer = nullptr;
	}

	// ���g�̔j��
	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CPlayer::Update(void)
{
	// �O��̈ʒu��ۑ�
	m_info.posOld = m_info.pos;

	// ��ԊǗ�
	ManageState();

	int nMotion = MOTION_NEUTRAL;

	if (m_info.pBody != nullptr)
	{
		nMotion = m_info.pBody->GetMotion();
	}

	if (nMotion != MOTION_APPER)
	{
		// ���쏈��
		Input();

		// ���[�V�����̊Ǘ�
		ManageMotion();

		// �ڕW��������������
		RotDest();

		float fScale = Slow::GetScale();

		// �ʒu�Ɉړ��ʂ𔽉f
		m_info.pos += m_info.move * fScale;

		// �����蔻��Ǘ�
		ManageCollision();

		// �ړ��ʌ���
		m_info.move.x += (0 - m_info.move.x) * m_param.fFactMove * fScale;

		if (m_info.pBody != nullptr)
		{
			if (m_info.pBody->GetMotion() != MOTION_DASH || m_info.pBody->IsFinish())
			{
				m_info.move.y -= m_param.fGravity * fScale;
			}
		}
	}
	else
	{
		if (m_info.pBody != nullptr)
		{
			if (m_info.pBody->IsFinish())
			{
				SetMotion(MOTION_NEUTRAL);

				// �^�C�}�[�𓮂���
				CTimer *pTimer = CTimer::GetInstance();

				if (pTimer != nullptr)
				{
					pTimer->EnableStop(false);
				}

				// �J���������̐ݒ�
				CCamera *pCamera = CManager::GetCamera();

				if (pCamera != nullptr)
				{
					pCamera->ChangeBehavior(new CCameraBehaviorFollowPlayer);
				}
			}
		}
	}

	if (m_info.pBody != nullptr)
	{// �̂̒Ǐ]
		m_info.pBody->SetPosition(m_info.pos);
		m_info.pBody->SetRot(m_info.rot);
	}

	if (m_info.pBody != nullptr)
	{// �e�̒Ǐ]

		float fHeight = 0.0f;

		// �u���b�N�̍������擾
		fHeight = CBlock::CheckShadow(GetPosition());

		// �e�̈ʒu�ݒ�
		m_info.pBody->SetPosShadow(D3DXVECTOR3(GetPosition().x, fHeight + 0.1f, GetPosition().z));
	}
}

//=====================================================
// ��ԊǗ�
//=====================================================
void CPlayer::ManageState(void)
{
	switch (m_info.state)
	{
	case CPlayer::STATE_NORMAL:
		break;
	case CPlayer::STATE_DAMAGE:

		m_info.nCntState++;

		if (m_info.nCntState >= m_param.nTimeDamage)
		{
			m_info.state = STATE_NORMAL;

			if (m_info.pBody != nullptr)
			{
				m_info.pBody->ResetAllCol();
			}

			m_info.nCntState = 0;
		}

		break;
	default:
		break;
	}
}

//=====================================================
// ���쏈��
//=====================================================
void CPlayer::Input(void)
{
	// �ړ�����
	InputMove();

	// �U������
	InputAttack();
}

//=====================================================
// �ړ�����
//=====================================================
void CPlayer::InputMove(void)
{
	// ������
	CInputMouse *pMouse = CInputMouse::GetInstance();
	CInputManager *pInputManager = CInputManager::GetInstance();
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();

	if (pMouse == nullptr || m_info.pBody == nullptr)
	{
		return;
	}

	D3DXVECTOR3 move = { 0.0f,0.0f,0.0f }, rot = { 0.0f,0.0f,0.0f };
	D3DXVECTOR3 vecStick;
	int nMotion = m_info.pBody->GetMotion();
	float fScale = Slow::GetScale();

	{// �U�����łȂ����
		if (nMotion != MOTION_PARRY ||
			m_info.jump > JUMPSTATE_NONE)
		{// �n��Ńp���B���ĂȂ���Έړ�
			if (pInputManager->GetPress(CInputManager::BUTTON_MOVE_LEFT))
			{// ���ړ�
				move.x -= m_param.fSpeedMove * fScale;
				m_info.rotDest.y = D3DX_PI * 0.5f;
			}
			if (pInputManager->GetPress(CInputManager::BUTTON_MOVE_RIGHT))
			{// �E�ړ�
				move.x += m_param.fSpeedMove * fScale;
				m_info.rotDest.y = -D3DX_PI * 0.5f;
			}

			// �W�����v����
			if (pInputManager->GetTrigger(CInputManager::BUTTON_JUMP))
			{
				if (m_info.jump == JUMPSTATE_NONE)
				{
					move.y += m_param.fPowJump;

					m_info.jump = JUMPSTATE_NORMAL;

					SetMotion(MOTION_JUMP);

					CAnimEffect3D *pAnim3D = CAnimEffect3D::GetInstance();

					if (pAnim3D != nullptr)
					{
						D3DXVECTOR3 posEffect = GetPosition();
						posEffect.y += 15.0f;
						posEffect.x += move.x;
						posEffect.z -= 5.0f;

						pAnim3D->CreateEffect(posEffect, CAnimEffect3D::TYPE_JUMP);
					}

					CSound *pSound = CSound::GetInstance();

					if (pSound != nullptr)
					{
						pSound->Play(CSound::LABEL_SE_JUMP);
					}
				}
				else if (m_info.jump == JUMPSTATE_NORMAL)
				{// �󒆍U��
					SetMotion(MOTION_AIRATTACK);

					D3DXVECTOR3 move = { GetMove().x,m_param.fPowAttackJump,GetMove().z };

					// �ړ��ʉ��Z
					SetMove(move);

					m_info.jump = JUMPSTATE_ATTACK;

					CAnimEffect3D *pAnim3D = CAnimEffect3D::GetInstance();

					if (pAnim3D != nullptr)
					{
						D3DXVECTOR3 posEffect = GetPosition();

						posEffect.y += 10.0f;

						pAnim3D->CreateEffect(posEffect, CAnimEffect3D::TYPE_AIRSLASH);
					}

					CSound *pSound = CSound::GetInstance();

					if (pSound != nullptr)
					{
						pSound->Play(CSound::LABEL_SE_AIRATTACK);
					}
				}

			}


			// �ړ��ʉ��Z
			SetMove(GetMove() + move);
		}
	}

#ifdef _DEBUG
	if (pKeyboard->GetTrigger(DIK_E))
	{// �{�X��܂Ń��[�v
		m_info.pos = { 2599.0f,204.57f,0.0f };
		m_info.posOld = { 2579.0f,204.57f,0.0f };
	}
#endif
}

//=====================================================
// �U������
//=====================================================
void CPlayer::InputAttack(void)
{
	// ������
	CInputManager *pInputManager = CInputManager::GetInstance();

	if (pInputManager == nullptr || m_info.pBody == nullptr)
	{
		return;
	}

	if (pInputManager->GetTrigger(CInputManager::BUTTON_ATTACK))
	{// �U��
		if (m_info.pBody->GetMotion() == MOTION_ATTACK || m_info.pBody->GetMotion() == MOTION_ATTACKTURN)
		{
			m_info.bAttack = true;
		}
		else
		{
			SetMotion(MOTION_ATTACK);

			m_info.bAttack = false;

			CSound *pSound = CSound::GetInstance();

			if (pSound != nullptr)
			{
				pSound->Play(CSound::LABEL_SE_ATTACK);
			}
		}
	}

	if (m_info.nCntDash >= m_param.nTimeDash)
	{
		if (pInputManager->GetTrigger(CInputManager::BUTTON_DASH))
		{// �_�b�V��
			if (m_info.pBody->GetMotion() != MOTION_DASH)
			{
				D3DXVECTOR3 move = GetMove();

				move.x -= sinf(m_info.rotDest.y) * m_param.fSpeedDash;
				move.y = 0;

				SetMove(move);

				SetMotion(MOTION_DASH);

				m_info.nCntDash = 0;

				CSound *pSound = CSound::GetInstance();

				if (pSound != nullptr)
				{
					pSound->Play(CSound::LABEL_SE_DASH);
				}
			}
		}
	}
	else
	{
		m_info.nCntDash++;
	}

	if (m_info.pBody != nullptr)
	{
		if (m_info.pBody->IsFinish())
		{// �A���̏���
			if (m_info.bAttack == true)
			{
				if (m_info.pBody->GetMotion() == MOTION_ATTACK)
				{
					SetMotion(MOTION_ATTACKTURN);

					m_info.bAttack = false;
				}
				else
				{
					SetMotion(MOTION_ATTACK);

					m_info.bAttack = false;
				}

				CSound *pSound = CSound::GetInstance();

				if (pSound != nullptr)
				{
					pSound->Play(CSound::LABEL_SE_ATTACK);
				}
			}
		}

		Parry();
	}
}

//=====================================================
// �p���B
//=====================================================
void CPlayer::Parry(void)
{
	// ������
	CInputManager *pInputManager = CInputManager::GetInstance();

	if (m_info.pBody == nullptr || m_info.pClsnAttack == nullptr)
	{
		return;
	}

	if (pInputManager->GetTrigger(CInputManager::BUTTON_PARRY) &&
		m_info.pBody->GetMotion() != MOTION_PARRY)
	{// �p���B
		SetMotion(MOTION_PARRY);

		m_info.nCntParry = 0;

		CSound *pSound = CSound::GetInstance();

		if (pSound != nullptr)
		{
			pSound->Play(CSound::LABEL_SE_ATTACK);
		}
	}

	if (m_info.nCntParry >= m_info.nTimeParry)
	{// �������牺�̓p���B�������ʂ�Ȃ�
		return;
	}
	else
	{
		m_info.nCntParry++;
	}

	D3DXMATRIX mtx;
	D3DXVECTOR3 pos;
	bool bHit = false;

	universal::SetOffSet(&mtx, *m_info.pBody->GetMatrix(), m_info.offsetParry);

	pos =
	{
		mtx._41,
		mtx._42,
		mtx._43
	};

	// �ʒu�ݒ�
	m_info.pClsnAttack->SetPosition(pos);
	
	// ���a�̐ݒ�
	m_info.pClsnAttack->SetRadius(m_info.fRadiusParry);

#ifdef _DEBUG
	//  CEffect3D::Create(pos, m_info.fRadiusParry, 10, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
#endif

	// �����������̔���
	bHit = m_info.pClsnAttack->SphereCollision(CCollision::TAG_ENEMYBULLET);

	// ���������I�u�W�F�N�g�̎擾
	CObject *pObj = m_info.pClsnAttack->GetOther();

	if (bHit == true && pObj != nullptr)
	{//	�p���B����
		D3DXVECTOR3 pos;
		D3DXVECTOR3 move;
		D3DXVECTOR3 posTarget;

		pos = pObj->GetPosition();

		// �G�̎擾
		CEnemyManager *pEnemyManager = CEnemyManager::GetInstance();

		CEnemy *pEnemy = nullptr;
		CEnemy *pLockEnemy = nullptr;
		float fLengthDest = FLT_MAX;

		if (pEnemyManager != nullptr)
		{
			pEnemy = pEnemyManager->GetHead();
		}

		int nNum = CEnemy::GetNumAll();

		while (pEnemy != nullptr)
		{
			// ���̃A�h���X��ۑ�
			CEnemy *pEnemyNext = pEnemy->GetNext();

			// �����x�N�g������ړ��ʂ�ݒ�
			posTarget = pEnemy->GetPosition();

			// �v���C���[�Ƃ̋����𑪂�
			D3DXVECTOR3 vecDiff;
			vecDiff = posTarget - pos;

			float fLength = D3DXVec3Length(&vecDiff);
			
			if (fLength < fLengthDest)
			{// �߂��G�̍X�V
				fLengthDest = fLength;
				pLockEnemy = pEnemy;
			}

			// ���̃A�h���X����
			pEnemy = pEnemyNext;
		}

		// �����x�N�g������ړ��ʂ�ݒ�
		posTarget = pLockEnemy->GetMtxPos(0);

		move = posTarget - pos;

		D3DXVec3Normalize(&move, &move);

		move *= BULLET_SPEED;

		pObj->Uninit();

		// �e�����e�̎ˏo
		CBullet::Create(pos, move, 200, CBullet::TYPE_PLAYER,false, BULLET_SIZE);

		CAnimEffect3D *pAnim3D = CAnimEffect3D::GetInstance();

		if (pAnim3D != nullptr)
		{
			pAnim3D->CreateEffect(pos, CAnimEffect3D::TYPE_SLASH);
			pAnim3D->CreateEffect(pos, CAnimEffect3D::TYPE_FLASH);
		}

		CParticle::Create(pos,CParticle::TYPE_FLASH);

		CSound *pSound = CSound::GetInstance();

		if (pSound != nullptr)
		{
			pSound->Play(CSound::LABEL_SE_PARRY);
		}
	}
}

//=====================================================
// ���[�V�����̊Ǘ�
//=====================================================
void CPlayer::ManageMotion(void)
{
	if (m_info.pBody == nullptr)
	{
		return;
	}

	// �ړ��ʂ̎擾
	D3DXVECTOR3 move = GetMove();

	bool bFinish = m_info.pBody->IsFinish();
	int nMotion = m_info.pBody->GetMotion();

	if (m_info.jump == JUMPSTATE_NONE)
	{
		if (m_info.bAttack == false &&
			(m_info.pBody->GetMotion() != MOTION_ATTACK && 
				m_info.pBody->GetMotion() != MOTION_ATTACKTURN && 
				m_info.pBody->GetMotion() != MOTION_PARRY &&
				m_info.pBody->GetMotion() != MOTION_DASH))
		{// �ړ����[�V����
			if (move.x * move.x > LINE_STOP * LINE_STOP)
			{// ������x�����Ă���Ε������[�V����
				SetMotion(MOTION_MOVE);
			}
			else
			{// �ҋ@���[�V�����ֈڍs
				SetMotion(MOTION_NEUTRAL);

				m_info.nCntAfterImage = 0;
			}
		}
		else
		{// �U�����[�V�����Ǘ�
			if (bFinish == true)
			{
				SetMotion(MOTION_NEUTRAL);
			}
		}
	}
	else
	{
		if (move.y < 0.0f && 
			(nMotion == MOTION_AIRATTACK && bFinish == false) == false &&
			(nMotion == MOTION_PARRY && bFinish == false) == false && 
			(nMotion == MOTION_ATTACK && bFinish == false) == false &&
			(nMotion == MOTION_ATTACKTURN && bFinish == false) == false &&
			(nMotion == MOTION_DASH && bFinish == false) == false)
		{// �������[�V����
			SetMotion(MOTION_FALL);
		}
	}

	// �ړ��ʂ̌v�Z
	float fSpeed = D3DXVec3Length(&move);

	if (nMotion == MOTION_AIRATTACK || nMotion == MOTION_APPER || nMotion == MOTION_DASH)
	{// ���胂�[�V�����̏ꍇ�Ɏc�����o��
		m_info.nCntAfterImage++;

		if (m_info.nCntAfterImage >= TIME_AFTERIMAGE)
		{
			// �c���̐���
			m_info.pBody->SetAfterImage(D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f), 20);

			m_info.nCntAfterImage = 0;
		}
	}
}

//=====================================================
// �����蔻��̊Ǘ�
//=====================================================
void CPlayer::ManageCollision(void)
{
	bool bLandFloor = false;
	bool bLandBlock = false;

	CFade *pFade = CFade::GetInstance();

	if (m_info.pCollisionCube != nullptr)
	{// �����蔻��̊Ǘ�

		m_info.pCollisionCube->SetPosition(GetPosition());

		D3DXVECTOR3 move = GetMove();

		// �����o���̓����蔻��
		bLandBlock = m_info.pCollisionCube->CubeCollision(CCollision::TAG_BLOCK, &move);

		SetMove(move);

		if (m_info.jump != JUMPSTATE_NONE && 
			bLandBlock)
		{
			m_info.jump = JUMPSTATE_NONE;
		}
		else if(bLandBlock == false && 
			m_info.jump == JUMPSTATE_NONE)
		{
			m_info.jump = JUMPSTATE_NORMAL;
		}
	}

	if (m_info.pClsnHit != nullptr)
	{
		if (m_info.pBody != nullptr)
		{
			if (m_info.pBody->GetParts(0) != nullptr)
			{
				D3DXMATRIX mtx = *m_info.pBody->GetParts(0)->m_pParts->GetMatrix();
				D3DXVECTOR3 pos =
				{
					mtx._41,
					mtx._42,
					mtx._43,
				};

				m_info.pClsnHit->SetPositionOld(m_info.pClsnHit->GetPosition());
				m_info.pClsnHit->SetPosition(pos);

				if (m_info.pClsnHit->SphereCollision(CCollision::TAG_ENEMY))
				{
					Hit(5.0f);
				}
			}
		}
	}

	// ����������=============
	if (m_info.pos.y <= -190.0f)
	{
		CFade *pFade = CFade::GetInstance();

		if (pFade != nullptr)
		{
			pFade->SetFade(MODE_DEATH);
		}
	}
	// =======================

	// �U������̊Ǘ�
	ManageAttack();
}

//=====================================================
// �U������̊Ǘ�
//=====================================================
void CPlayer::ManageAttack(void)
{
	if (m_info.pClsnAttack == nullptr)
	{// ����̃G���[
		return;
	}

	if (m_info.pBody == nullptr)
	{// ���[�V�����̃G���[
		return;
	}

	for (int i = 0; i < m_info.nNumAttack; i++)
	{
		if (m_info.pBody->GetMotion() == m_info.pAttackInfo[i].nIdxMotion)
		{// �U�����[�V�������̔���
			float fFrame = m_info.pBody->GetFrame();
			int nKey = m_info.pBody->GetKey();
			D3DXVECTOR3 pos;

			if (fFrame == m_info.pAttackInfo[i].nFrame && nKey == m_info.pAttackInfo[i].nKey)
			{// �����蔻��̐ݒ�
				bool bHit = false;
				D3DXMATRIX mtx;

				universal::SetOffSet(&mtx, *m_info.pBody->GetMatrix(), m_info.pAttackInfo[i].pos);

				pos =
				{
					mtx._41,
					mtx._42,
					mtx._43
				};

#ifdef _DEBUG
				CEffect3D::Create(pos, m_info.pAttackInfo[i].fRadius, 10, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	// �U������̉���
#endif

				// �ʒu�ݒ�
				m_info.pClsnAttack->SetPosition(pos);
				
				// ���a�̐ݒ�
				m_info.pClsnAttack->SetRadius(m_info.pAttackInfo[i].fRadius);

				bHit = m_info.pClsnAttack->SphereCollision(CCollision::TAG_ENEMY);
				CObject *pObj = m_info.pClsnAttack->GetOther();

				if (bHit == true && pObj != nullptr)
				{// �������̃q�b�g����
					// �A�j���[�V�����G�t�F�N�g�̍Đ�
					CAnimEffect3D *pAnim3D = CAnimEffect3D::GetInstance();

					if (pAnim3D != nullptr)
					{
						pAnim3D->CreateEffect(pos, CAnimEffect3D::TYPE_FLASH);
					}

					// ���������I�u�W�F�N�g�̃q�b�g����
					pObj->Hit(5.0f);

					// ���̍Đ�
					CSound *pSound = CSound::GetInstance();

					if (pSound != nullptr)
					{
						pSound->Play(CSound::LABEL_SE_HIT_NORMAL);
					}

					// �q�b�g�X�g�b�v�̔���
					CSlow *pSlow = CSlow::GetInstance();

					if (pSlow != nullptr)
					{
						pSlow->SetSlowTime(m_info.pAttackInfo[i].fTimeHitStop, m_info.pAttackInfo[i].fScaleHitStop);
					}
				}
			}
		}
	}
}

//=====================================================
// �ڕW��������������
//=====================================================
void CPlayer::RotDest(void)
{
	D3DXVECTOR3 vecDest;
	D3DXVECTOR3 rot = GetRot();

	float fRotDiff = m_info.rotDest.y - rot.y;

	// �p�x�̏C��
	if (fRotDiff > D3DX_PI)
	{
		fRotDiff -= 6.28f;
	}
	if (fRotDiff < -D3DX_PI)
	{
		fRotDiff += 6.28f;
	}

	// �p�x�␳
	SetRot(D3DXVECTOR3(rot.x, rot.y + fRotDiff * m_param.fFactRoll, rot.z));

	// �p�x�̏C��
	rot = GetRot();

	if (GetRot().y > D3DX_PI)
	{
		// �p�x�␳
		SetRot(D3DXVECTOR3(GetRot().x, GetRot().y - 6.28f, GetRot().z));
	}
	if (GetRot().y < -D3DX_PI)
	{
		// �p�x�␳
		SetRot(D3DXVECTOR3(GetRot().x, GetRot().y + 6.28f, GetRot().z));
	}
}

//=====================================================
// �q�b�g����
//=====================================================
void CPlayer::Hit(float fDamage)
{
	if (m_info.pBody != nullptr)
	{
		if (m_info.pBody->GetMotion() == MOTION_DASH)
		{
			return;
		}
	}

	if (m_info.state == STATE_NORMAL)
	{
		CSound *pSound = CSound::GetInstance();

		if (pSound != nullptr)
		{
			pSound->Play(CSound::LABEL_SE_DAMAGE);
		}

		m_info.nLife -= (int)fDamage;

		if (m_info.nLife <= 0)
		{// ���S����
			m_info.nLife = 0;

			Death();
		}
		else
		{
			m_info.state = STATE_DAMAGE;

			CManager::GetCamera()->SetQuake(0.03f, 0.03f, 10);

			if (m_info.pBody != nullptr)
			{
				m_info.pBody->SetAllCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			}
		}
	}
}

//=====================================================
// ���[�V�����ݒ�
//=====================================================
void CPlayer::SetMotion(MOTION motion)
{
	if (m_info.pBody == nullptr)
	{
		return;
	}

	if (m_info.pBody->GetMotion() != motion)
	{
		// ���[�V�����ݒ�
		m_info.pBody->SetMotion(motion);
	}
}

//=====================================================
// ���S����
//=====================================================
void CPlayer::Death(void)
{
	CFade *pFade = CFade::GetInstance();

	if (pFade != nullptr)
	{
		pFade->SetFade(MODE_DEATH);
	}

	Uninit();
}

//=====================================================
// �`�揈��
//=====================================================
void CPlayer::Draw(void)
{
	if (m_info.pBody != nullptr)
	{
		m_info.pBody->SetMatrix();
	}

#ifdef _DEBUG
	CDebugProc::GetInstance()->Print("\n�v���C���[�̈ʒu�F[%f,%f,%f]", GetPosition().x, GetPosition().y, GetPosition().z);
	CDebugProc::GetInstance()->Print("\n�v���C���[�̗�[%d]", m_info.nLife);
	CDebugProc::GetInstance()->Print("\n�U��[%d]", m_info.bAttack);
#else
	CDebugProc::GetInstance()->Print("\n");
	CDebugProc::GetInstance()->Print("//----------------------------\n");
	CDebugProc::GetInstance()->Print("// �v���C���[��{����\n");
	CDebugProc::GetInstance()->Print("//----------------------------\n");
	CDebugProc::GetInstance()->Print("[A D]�ړ�\n");
	CDebugProc::GetInstance()->Print("[LMB]�U��\n");
	CDebugProc::GetInstance()->Print("[RMB]�e�p���B\n");
	CDebugProc::GetInstance()->Print("[SPACE]�W�����v\n");
	CDebugProc::GetInstance()->Print("\n");
#endif
}

//=====================================================
// ��������
//=====================================================
CPlayer *CPlayer::Create(void)
{
	if (m_pPlayer == nullptr)
	{
		m_pPlayer = new CPlayer;

		if (m_pPlayer != nullptr)
		{
			m_pPlayer->Init();
		}
	}

	return m_pPlayer;
}

//=====================================================
// ���Ǎ�
//=====================================================
void CPlayer::Load(void)
{
	// �ϐ��錾
	char cTemp[256];
	int nCntAttack = 0;

	// �t�@�C������ǂݍ���
	FILE *pFile = fopen(PARAM_PATH, "r");

	if (pFile != nullptr)
	{// �t�@�C�����J�����ꍇ
		while (true)
		{
			// �����ǂݍ���
			fscanf(pFile, "%s", &cTemp[0]);

			// �p�����[�^�[�Ǎ�
			LoadParam(pFile,&cTemp[0]);

			if (strcmp(cTemp, "NUM_ATTACK") == 0)
			{// �U������Ǎ��J�n
				// �U�����萔�Ǎ�
				fscanf(pFile, "%s", &cTemp[0]);

				fscanf(pFile, "%d", &m_info.nNumAttack);
				
				if (m_info.pAttackInfo == nullptr)
				{// ������̐���
					m_info.pAttackInfo = new AttackInfo[m_info.nNumAttack];

					for (int i = 0; i < m_info.nNumAttack; i++)
					{// ���̃N���A
						ZeroMemory(&m_info.pAttackInfo[i], sizeof(AttackInfo));

						// �q�b�g�X�g�b�v���̏�����
						m_info.pAttackInfo[i].fScaleHitStop = 1.0f;
						m_info.pAttackInfo[i].fTimeHitStop = 0.0f;
					}
				}
				else
				{
					break;
				}

				if (m_info.pAttackInfo == nullptr)
				{// �����ł��Ȃ������ꍇ
					break;
				}

				while (true)
				{
					// �����ǂݍ���
					fscanf(pFile, "%s", &cTemp[0]);

					if (strcmp(cTemp, "ATTACKSET") == 0)
					{// �p�����[�^�[�Ǎ��J�n
						while (true)
						{
							// �����ǂݍ���
							fscanf(pFile, "%s", &cTemp[0]);

							if (strcmp(cTemp, "MOTION") == 0)
							{// ���[�V�����̎��
								fscanf(pFile, "%s", &cTemp[0]);

								fscanf(pFile, "%d", &m_info.pAttackInfo[nCntAttack].nIdxMotion);
							}

							if (strcmp(cTemp, "POS") == 0)
							{//�ʒu�ǂݍ���
								fscanf(pFile, "%s", &cTemp[0]);

								for (int nCntPos = 0; nCntPos < 3; nCntPos++)
								{
									fscanf(pFile, "%f", &m_info.pAttackInfo[nCntAttack].pos[nCntPos]);
								}
							}

							if (strcmp(cTemp, "KEY") == 0)
							{// �L�[�̔ԍ�
								fscanf(pFile, "%s", &cTemp[0]);

								fscanf(pFile, "%d", &m_info.pAttackInfo[nCntAttack].nKey);
							}

							if (strcmp(cTemp, "FRAME") == 0)
							{// �t���[���ԍ�
								fscanf(pFile, "%s", &cTemp[0]);

								fscanf(pFile, "%d", &m_info.pAttackInfo[nCntAttack].nFrame);
							}

							if (strcmp(cTemp, "RADIUS") == 0)
							{// ���a
								fscanf(pFile, "%s", &cTemp[0]);

								fscanf(pFile, "%f", &m_info.pAttackInfo[nCntAttack].fRadius);
							}

							if (strcmp(cTemp, "SCALE_HITSTOP") == 0)
							{// �q�b�g�X�g�b�v�̃^�C���X�P�[��
								fscanf(pFile, "%s", &cTemp[0]);

								fscanf(pFile, "%f", &m_info.pAttackInfo[nCntAttack].fScaleHitStop);
							}

							if (strcmp(cTemp, "TIME_HITSTOP") == 0)
							{// �q�b�g�X�g�b�v�p������
								fscanf(pFile, "%s", &cTemp[0]);

								fscanf(pFile, "%f", &m_info.pAttackInfo[nCntAttack].fTimeHitStop);
							}

							if (strcmp(cTemp, "END_ATTACKSET") == 0)
							{// �p�����[�^�[�Ǎ��I��
								nCntAttack++;

								break;
							}
						}
					}

					if (m_info.nNumAttack <= nCntAttack)
					{
						break;
					}
				}
			}

			if (strcmp(cTemp, "PARRYSET") == 0)
			{// �p���B����Ǎ��J�n
				while (true)
				{
					// �����ǂݍ���
					fscanf(pFile, "%s", &cTemp[0]);

					if (strcmp(cTemp, "POS") == 0)
					{//�ʒu�ǂݍ���
						fscanf(pFile, "%s", &cTemp[0]);

						for (int i = 0; i < 3; i++)
						{
							fscanf(pFile, "%f", &m_info.offsetParry[i]);
						}
					}

					if (strcmp(cTemp, "RADIUS") == 0)
					{// ���a
						fscanf(pFile, "%s", &cTemp[0]);

						fscanf(pFile, "%f", &m_info.fRadiusParry);
					}

					if (strcmp(cTemp, "TIME") == 0)
					{// �p���B�p������
						fscanf(pFile, "%s", &cTemp[0]);

						fscanf(pFile, "%d", &m_info.nTimeParry);
					}
					
					if (strcmp(cTemp, "END_PARRYSET") == 0)
					{// �p�����[�^�[�Ǎ��I��
						nCntAttack++;

						break;
					}
				}
			}

			if (strcmp(cTemp, "END_SCRIPT") == 0)
			{// �I������
				break;
			}
		}

		// �t�@�C�������
		fclose(pFile);
	}
}

//=====================================================
// �p�����[�^�[�Ǎ�
//=====================================================
void CPlayer::LoadParam(FILE *pFile, char *pTemp)
{
	if (strcmp(pTemp, "BODY") == 0)
	{// �����ڂ̓ǂݍ���
		fscanf(pFile, "%s", pTemp);

		fscanf(pFile, "%s", pTemp);

		if (m_info.pBody == nullptr)
		{// �̂̐���
			m_info.pBody = CMotion::Create(pTemp);

			if (m_info.pBody != nullptr)
			{
				m_info.pBody->EnableShadow(true);
			}
		}
	}

	if (strcmp(pTemp, "LIFE") == 0)
	{// �̗�
		fscanf(pFile, "%s", pTemp);

		fscanf(pFile, "%d", &m_param.nInitialLife);

		m_info.nLife = m_param.nInitialLife;
	}

	if (strcmp(pTemp, "SPEED_MOVE") == 0)
	{// �ʏ�ڑ��x
		fscanf(pFile, "%s", pTemp);

		fscanf(pFile, "%f", &m_param.fSpeedMove);
	}

	if (strcmp(pTemp, "GRAVITY") == 0)
	{// �d��
		fscanf(pFile, "%s", pTemp);

		fscanf(pFile, "%f", &m_param.fGravity);
	}

	if (strcmp(pTemp, "MOVE_FACT") == 0)
	{// �ړ������W��
		fscanf(pFile, "%s", pTemp);

		fscanf(pFile, "%f", &m_param.fFactMove);
	}

	if (strcmp(pTemp, "ROLL_FACT") == 0)
	{// �ړ������W��
		fscanf(pFile, "%s", pTemp);

		fscanf(pFile, "%f", &m_param.fFactRoll);
	}

	if (strcmp(pTemp, "TIME_DASH") == 0)
	{// �_�b�V���̃N�[���^�C��
		fscanf(pFile, "%s", pTemp);

		fscanf(pFile, "%d", &m_param.nTimeDash);
	}

	if (strcmp(pTemp, "SPEED_DASH") == 0)
	{// �_�b�V���̑��x
		fscanf(pFile, "%s", pTemp);

		fscanf(pFile, "%f", &m_param.fSpeedDash);
	}

	if (strcmp(pTemp, "JUMP_POW") == 0)
	{// �W�����v��
		fscanf(pFile, "%s", pTemp);

		fscanf(pFile, "%f", &m_param.fPowJump);
	}

	if (strcmp(pTemp, "ATTACKJUMP_POW") == 0)
	{// �W�����v��
		fscanf(pFile, "%s", pTemp);

		fscanf(pFile, "%f", &m_param.fPowAttackJump);
	}

	if (strcmp(pTemp, "TIME_DAMAGE") == 0)
	{// ���G����
		fscanf(pFile, "%s", pTemp);

		fscanf(pFile, "%d", &m_param.nTimeDamage);
	}
}