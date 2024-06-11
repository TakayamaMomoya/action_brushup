//*****************************************************
//
// �{�X�G�̏���[enemyboss.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "enemyboss.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "universal.h"
#include "debugproc.h"
#include "game.h"
#include "bullet.h"
#include "missile.h"
#include "effect3D.h"
#include "frame.h"
#include "shadow.h"
#include "score.h"
#include "sound.h"
#include "particle.h"
#include "slow.h"
#include "camera.h"
#include "cameraState.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const float INITIAL_LIFE = 60.0f;	// �����̗�
const int INITIAL_SCORE = 3000;	// �����X�R�A
const float ROLL_FACT = 0.1f;	// ��]�W��
const float MOVE_FACT = 0.04f;	// �ړ��ʌ����W��
const float LINE_END_MOVE = 5.0f;	// �ړ��I���̂������l
const float MID_POINT = 2740.0f;	// �{�X��X�e�[�W�̒���X���W
const float WIDTH_STAGE = 160.0f;	// �X�e�[�W�̕�
const float TIME_DAMAGE = 0.2f;	// ���G����
const float FLOAT_HEIGHT = 180.0f;	// ������ł��鍂��
const float SHOT_HEIGHT = 30.0f;	// �ˌ����̍���
const float RADIUS_COLLISION = 35.0f;	// �����蔻��̔��a
const float SIZE_SHADOW = 40.0f;	// �e�̃T�C�Y
}

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CEnemyBoss *CEnemyBoss::m_pEnemyBoss = nullptr;	// ���g�̃|�C���^

//=====================================================
// �R���X�g���N�^
//=====================================================
CEnemyBoss::CEnemyBoss() : m_pState(nullptr), m_info()
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CEnemyBoss::~CEnemyBoss()
{

}

//=====================================================
// ��������
//=====================================================
CEnemyBoss *CEnemyBoss::Create(void)
{
	if (m_pEnemyBoss == nullptr)
	{
		m_pEnemyBoss = new CEnemyBoss;
	}

	return m_pEnemyBoss;
}

//=====================================================
// ����������
//=====================================================
HRESULT CEnemyBoss::Init(void)
{
	typeid(CEnemyBossStateDash);

	CSound *pSound = CSound::GetInstance();

	if (pSound != nullptr)
	{
		pSound->Stop();

		pSound->Play(CSound::LABEL_BGM_BOSS);
	}

	// �t���[�����o�̐���
	CFrame::Create(100, 240, 70);

	// �p���N���X�̏�����
	CEnemy::Init();

	// �����̗̑͐ݒ�
	SetLife(INITIAL_LIFE);

	// �X�R�A�ݒ�
	SetScore(INITIAL_SCORE);

	// �e�̐ݒ�
	CShadow *pShadow = GetShadow();

	if (pShadow != nullptr)
	{
		pShadow->SetSize(SIZE_SHADOW, SIZE_SHADOW);
	}

	// �J�������{�X�o���̂��̂ɕύX
	CCamera *pCamera = CManager::GetCamera();

	if (pCamera != nullptr)
	{
		pCamera->ChangeState(new CCameraStateApperBoss);
	}

	// �X�e�C�g�̐؂�ւ�
	ChangeState(new CEnemyBossStateApper);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CEnemyBoss::Uninit(void)
{
	CParticle::Create(GetMtxPos(0), CParticle::TYPE_EXPLOSION);

	CSound *pSound = CSound::GetInstance();

	if (pSound != nullptr)
	{
		pSound->Play(CSound::LABEL_SE_EXPLOSION);
	}

	m_pEnemyBoss = nullptr;

	// �p���N���X�̏I��
	CEnemy::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CEnemyBoss::Update(void)
{
	// �ʒu��ۑ�
	SetPositionOld(GetPosition());

	// �p���N���X�̍X�V
	CEnemy::Update();

	// ��ԊǗ�
	ManageState();

	if (m_pState != nullptr)
	{// �X�e�C�g�̍X�V
		m_pState->Update(this);
	}
	
	// �����蔻��Ǘ�
	ManageCollision();
}

//=====================================================
// ��ԊǗ�
//=====================================================
void CEnemyBoss::ManageState(void)
{
	CEnemy::STATE state = CEnemy::GetState();

	float fTimer = GetCntState();
	float fAddTime = CManager::GetDeltaTime() * Slow::GetTimeScale();

	switch (state)
	{
	case CEnemy::STATE_NORMAL:
		break;
	case CEnemy::STATE_DAMAGE:

		fTimer += fAddTime;

		SetAllCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

		if (fTimer > TIME_DAMAGE)
		{// �ʏ��Ԃɖ߂�
			fTimer = 0;
			state = CEnemy::STATE_NORMAL;

			ResetAllCol();
		}
		break;
	case CEnemy::STATE_DEATH:
		if (m_info.fTimerState >= 180)
		{
			Death();
		}
		else
		{
			m_info.fTimerState++;
		}

		break;
	default:
		break;
	}

	CEnemy::SetState(state);

	SetCntState(fTimer);
}

//=====================================================
// �����蔻��Ǘ�
//=====================================================
void CEnemyBoss::ManageCollision(void)
{
	// �����蔻��Ǐ]
	FollowCollision();
}

//=====================================================
// �����蔻��̒Ǐ]
//=====================================================
void CEnemyBoss::FollowCollision(void)
{
	CCollisionSphere *pCollision = GetClsnSphere();

	if (pCollision != nullptr)
	{
		D3DXVECTOR3 pos = GetMtxPos(IDX_WAIST);

		pCollision->SetPositionOld(pCollision->GetPosition());
		pCollision->SetPosition(pos);
		pCollision->SetRadius(RADIUS_COLLISION);
	}
}

//=====================================================
// �X�e�C�g�̐؂�ւ�
//=====================================================
void CEnemyBoss::ChangeState(CEnemyBossState *pState)
{
	if (m_pState != nullptr)
	{
		delete m_pState;
		m_pState = nullptr;
	}

	m_pState = pState;

	if (m_pState != nullptr)
	{
		m_pState->Init(this);
	}
}

//=====================================================
// �ڕW�ʒu�ւ̈ړ�
//=====================================================
bool CEnemyBoss::FollowDest(void)
{
	bool bEnd = false;

	D3DXVECTOR3 pos = GetPosition();

	D3DXVECTOR3 vecDiff = m_info.posDest - pos;

	// ���������̎擾
	float fLength = D3DXVec3Length(&vecDiff);

	if (LINE_END_MOVE > fLength)
	{
		bEnd = true;
	}

	vecDiff *= MOVE_FACT;

	pos += vecDiff;

	SetPosition(pos);

	return bEnd;
}

//=====================================================
// ��Ԃ̐؂�ւ�
//=====================================================
void CEnemyBoss::SwitchState(void)
{
	ATTACKSTATE state;

	// ��Ԃ�U��
	state = (ATTACKSTATE)(rand() % (ATTACK_MAX));

	while (m_info.attackState == state)
	{
		state = (ATTACKSTATE)(rand() % (ATTACK_MAX));
	}

	m_info.attackState = state;

	// �X�e�C�g�̐���
	CEnemyBossState *pState = nullptr;

	switch (m_info.attackState)
	{
	case ATTACK_MISSILE:
		pState = new CEnemyBossStateMissile;
		break;
	case ATTACK_DASH:
		pState = new CEnemyBossStateDash;
		break;
	case ATTACK_SHOT:
		pState = new CEnemyBossStateShot;
		break;
	default:
		break;
	}

	// ��Ԃ̐؂�ւ�
	ChangeState(pState);
}

//=====================================================
// �q�b�g����
//=====================================================
void CEnemyBoss::Hit(float fDamage)
{
	CEnemy::STATE state = CEnemy::GetState();

	if (state == CEnemy::STATE_NORMAL)
	{
		float fLife = CEnemy::GetLife();

		fLife -= fDamage;

		CSound *pSound = CSound::GetInstance();

		if (pSound != nullptr)
		{
			pSound->Play(CSound::LABEL_SE_HIT_BOSS);
		}

		if (fLife <= 0.0f)
		{// ���S���
			fLife = 0.0f;

			// ���[�V�����̐ݒ�
			SetMotion(MOTION_DEATH);

			// �p�[�e�B�N���̔���
			CParticle::Create(GetMtxPos(IDX_WAIST), CParticle::TYPE_FIRE);

			// �Q�[�����I����Ԃɂ���
			CGame::SetState(CGame::STATE_END);

			// ���S��ԂɕύX
			m_info.state = STATE_NONE;
			state = CEnemy::STATE_DEATH;

			// �X�R�A�Ǘ�
			ManageScore();

			// �X�R�A�ݒ�
			CScore *pScore = CScore::GetInstance();

			if (pScore != nullptr)
			{
				pScore->SetResultScore();
			}

			// �����蔻��폜
			DeleteCollision();

			if (m_pState != nullptr)
			{// �X�e�C�g�̔j��
				delete m_pState;
				m_pState = nullptr;
			}
		}
		else
		{
			state = CEnemy::STATE_DAMAGE;
		}

		CEnemy::SetLife(fLife);
	}

	CEnemy::SetState(state);
}

//=====================================================
// �`�揈��
//=====================================================
void CEnemyBoss::Draw(void)
{
	// �p���N���X�̕`��
	CEnemy::Draw();

#ifdef _DEBUG
	CDebugProc::GetInstance()->Print("\n�{�X�ʒu�F[%f,%f,%f]", GetPosition().x, GetPosition().y, GetPosition().z);
	CDebugProc::GetInstance()->Print("\n�{�X�̗́F[%f]", GetLife());
	CDebugProc::GetInstance()->Print("\n�{�X��ԁF[%d]",CEnemy::GetState());
	CDebugProc::GetInstance()->Print("\n�{�X���[�V�����F[%d]", GetMotion());
	CDebugProc::GetInstance()->Print("\n�L�[�F[%d]", GetKey());
	CDebugProc::GetInstance()->Print("\n�t���[���F[%d]", GetFrame());
	CDebugProc::GetInstance()->Print("\nIsFinish�F[%d]", IsFinish());
#endif
}