//*****************************************************
//
// �G�̏���[enemy.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "enemy.h"
#include "manager.h"
#include "score.h"
#include "collision.h"
#include "debugproc.h"
#include "particle.h"
#include "player.h"
#include "game.h"
#include "enemyshot.h"
#include "enemyManager.h"
#include "shadow.h"
#include "slow.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const float INITIAL_LIFE = 5.0f;	// �����̗�
const float TIME_DAMAGE = 0.1f;	// �_���[�W��Ԃ̌p������
const int INITIAL_SCORE = 1000;	// �����X�R�A
const float TIME_DEATH = 0.5f;	// ���S��̏����鎞��
const float ROLL_FACT = 0.1f;	// ��]�W��
const float INITIAL_SIZE_SHADOW = 10.0f;	// �e�̏����T�C�Y
const float SLOW_TIME_DEATH = 0.4f;	// ���S���ɂ�����X���[�̌p������
const float SLOW_SCALE_DEATH = 0.3f;	// ���S���ɂ�����X���[�̃^�C���X�P�[��
}

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
int CEnemy::m_nNumAll = 0;	// ����

//=====================================================
// �R���X�g���N�^
//=====================================================
CEnemy::CEnemy() : m_fLife(0.0f),m_nScore(0),m_fTimerState(0.0f),m_pCollisionCube(nullptr),m_pCollisionSphere(nullptr),m_pShadow(nullptr),
					m_state(STATE_NORMAL),m_pNext(nullptr),m_pPrev(nullptr)
{
	// �����J�E���g�A�b�v
	m_nNumAll++;

	// �擪�A�Ō���A�h���X�擾
	CEnemyManager *pManager = CEnemyManager::GetInstance();
	CEnemy *pHead = nullptr;
	CEnemy *pTail = nullptr;

	if (pManager != nullptr)
	{
		pHead = pManager->GetHead();
		pTail = pManager->GetTail();
	}

	if (pHead == nullptr)
	{// �擪�ƍŌ���A�h���X�̑��
		pManager->SetHead(this);
		pManager->SetTail(this);

		return;
	}

	// �O�̃A�h���X�ɍŌ���̃A�h���X��������
	m_pPrev = pTail;

	// �Ō���̃A�h���X�������ɂ���
	pManager->SetTail(this);

	if (m_pPrev != nullptr)
	{
		// �O�̃I�u�W�F�N�g�̎��̃A�h���X�������ɂ���
		m_pPrev->m_pNext = this;
	}
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CEnemy::~CEnemy()
{
	// �擪�A�Ō���A�h���X�擾
	CEnemyManager *pManager = CEnemyManager::GetInstance();
	CEnemy *pHead = nullptr;
	CEnemy *pTail = nullptr;

	if (pManager != nullptr)
	{
		pHead = pManager->GetHead();
		pTail = pManager->GetTail();
	}

	if (m_state != STATE_DEATH)
	{
		m_nNumAll--;
	}

	if (pHead == this)
	{// �擪�A�h���X�̔j��
		//if (m_pNext != nullptr)
		{// �擪�A�h���X�����̃A�h���X�Ɉ����p��
			pManager->SetHead(m_pNext);

			if (m_pNext != nullptr)
			{
				m_pNext->m_pPrev = nullptr;
			}
		}
	}
	else if (pTail == this)
	{// �Ō���A�h���X�̔j��
		if (m_pPrev != nullptr)
		{// �Ō���A�h���X��O�̃A�h���X�Ɉ����p��
			pManager->SetTail(m_pPrev);

			m_pPrev->m_pNext = nullptr;
		}
	}
	else
	{// �^�񒆂̃A�h���X�̔j��
		if (m_pPrev != nullptr)
		{
			// �O�̃A�h���X���玟�̃A�h���X���Ȃ�
			m_pPrev->m_pNext = m_pNext;
		}

		if (m_pNext != nullptr)
		{
			// ���̃A�h���X����O�̃A�h���X���Ȃ�
			m_pNext->m_pPrev = m_pPrev;
		}
	}
}

//=====================================================
// ��������
//=====================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, TYPE type)
{
	CEnemy *pEnemy = nullptr;

	if (pEnemy == nullptr)
	{// �C���X�^���X����
		switch (type)
		{
		case TYPE_SHOT:

			pEnemy = new CEnemyShot;

			pEnemy->CMotion::Load("data\\MOTION\\robot00.txt");

			pEnemy->SetMotion(0);

			break;
		default:
			break;
		}

		// �ʒu�ݒ�
		pEnemy->SetPosition(pos);

		// ����������
		pEnemy->Init();
	}

	return pEnemy;
}

//=====================================================
// ����������
//=====================================================
HRESULT CEnemy::Init(void)
{
	// �ł��傫���p�[�c�̔��a�擾
	float fRadius = GetRadiusMax();

	// �p���N���X�̏�����
	CMotion::Init();

	// �^�C�v�̐ݒ�
	SetType(TYPE_ENEMY);

	if (m_pCollisionSphere == nullptr)
	{// ���̓����蔻�萶��
		m_pCollisionSphere = CCollisionSphere::Create(CCollision::TAG_ENEMY, CCollision::TYPE_SPHERE,this);

		if (m_pCollisionSphere != nullptr)
		{// ���̐ݒ�
			m_pCollisionSphere->SetPosition(GetPosition());
			m_pCollisionSphere->SetRadius(fRadius);
		}
	}

	if (m_pCollisionCube == nullptr)
	{// �����̂̓����蔻��
		m_pCollisionCube = CCollisionCube::Create(CCollision::TAG_ENEMY, this);

		D3DXVECTOR3 vtxMax = { fRadius,fRadius,fRadius };
		D3DXVECTOR3 vtxMin = { -fRadius,-fRadius,-fRadius };

		if (m_pCollisionCube != nullptr)
		{
			m_pCollisionCube->SetVtx(vtxMax, vtxMin);
		}
	}

	// �̗͂̏����ݒ�
	m_fLife = INITIAL_LIFE;

	// �ʏ��Ԃɂ���
	m_state = STATE_NORMAL;

	m_nScore = INITIAL_SCORE;

	if (m_pShadow == nullptr)
	{// �e�̐���
		m_pShadow = CShadow::Create(GetPosition(), INITIAL_SIZE_SHADOW, INITIAL_SIZE_SHADOW);
	}

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CEnemy::Uninit(void)
{
	// �����蔻��폜
	DeleteCollision();

	if (m_pShadow != nullptr)
	{
		m_pShadow->Uninit();
		m_pShadow = nullptr;
	}

	// �p���N���X�̏I��
	CMotion::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CEnemy::Update(void)
{
	// �p���N���X�̍X�V
	CMotion::Update();

	if (m_state != STATE_DEATH)
	{
		if (m_pShadow != nullptr)
		{// �e�̒Ǐ]
			D3DXVECTOR3 pos = GetMtxPos(0);

			m_pShadow->SetPosition(pos);
		}
	}
}

//=====================================================
// ��ԊǗ�
//=====================================================
void CEnemy::ManageState(void)
{
	D3DXCOLOR col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	float fAddTime = CManager::GetDeltaTime() * Slow::GetTimeScale();

	switch (m_state)
	{
	case STATE_NORMAL:
		break;
	case STATE_DAMAGE:
		if (m_fTimerState > TIME_DAMAGE)
		{// �ʏ��Ԃɖ߂�
			m_fTimerState = 0;
			m_state = STATE_NORMAL;
		}
		else
		{// �J�E���g�A�b�v
			m_fTimerState += fAddTime;
		}

		break;
	case STATE_DEATH:

		m_fTimerState += fAddTime;

		// �����ɂȂ�Ȃ��������
		col = D3DXCOLOR(1.0f,0.0f,0.0f,1.0f);

		col.a = 1.0f - (m_fTimerState / (TIME_DEATH));

		SetAllCol(col);

		if (m_fTimerState >= TIME_DEATH)
		{// ���S
			Death();
		}

		break;
	default:
		break;
	}
}

//=====================================================
// �ڕW��������������
//=====================================================
void CEnemy::RotDest(void)
{
	// �ڕW�擾
	CPlayer *pPlayer;
	if (CPlayer::GetInstance() != nullptr)
	{
		pPlayer = CPlayer::GetInstance();
	}
	else
	{
		return;
	}

	D3DXVECTOR3 posTarget = pPlayer->GetPosition();
	D3DXVECTOR3 pos = GetPosition();
	float fRot = 0.0f;

	if (posTarget.x <= pos.x)
	{// �E��
		fRot = D3DX_PI * 0.5f;
	}
	else
	{// ����
		fRot = -D3DX_PI * 0.5f;
	}

	// �ϐ��錾
	D3DXVECTOR3 vecDest;
	D3DXVECTOR3 rot = GetRot();

	float fRotDiff = fRot - rot.y;

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
	SetRot(D3DXVECTOR3(rot.x, rot.y + fRotDiff * ROLL_FACT, rot.z));

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
// �̗͐ݒ�
//=====================================================
void CEnemy::SetLife(float fLife)
{
	m_fLife = fLife;

	if (m_fLife < 0)
	{
		m_fLife = 0;
	}
}

//=====================================================
// �q�b�g����
//=====================================================
void CEnemy::Hit(float fDamage)
{
	if (m_state == STATE_NORMAL)
	{
		m_fLife -= fDamage;

		if (m_fLife <= 0.0f)
		{// ���S���
			m_fLife = 0.0f;

			m_state = STATE_DEATH;

			// �X�R�A�Ǘ�
			ManageScore();

			// �����蔻��폜
			DeleteCollision();

			// �q�b�g�X�g�b�v��������
			CSlow *pSlow = CSlow::GetInstance();

			if (pSlow != nullptr)
			{
				pSlow->SetSlowTime(SLOW_TIME_DEATH, SLOW_SCALE_DEATH);
			}
		}
		else
		{// �_���[�W��ԂɂȂ�
			m_state = STATE_DAMAGE;
		}
	}
}

//=====================================================
// ���S����
//=====================================================
void CEnemy::Death(void)
{
	// ���g�̏I��
	Uninit();
}

//=====================================================
// �����蔻��폜
//=====================================================
void CEnemy::DeleteCollision(void)
{
	if (m_pCollisionSphere != nullptr)
	{// �����蔻��̏���
		m_pCollisionSphere->Uninit();

		m_pCollisionSphere = nullptr;
	}

	if (m_pCollisionCube != nullptr)
	{// �����蔻��̏���
		m_pCollisionCube->Uninit();

		m_pCollisionCube = nullptr;
	}
}

//=====================================================
// �X�R�A�Ǘ�
//=====================================================
void CEnemy::ManageScore(void)
{
	CScore *pScore = CScore::GetInstance();

	if (pScore != nullptr)
	{
		int nScore = GetScore();

		pScore->AddScore(nScore);
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CEnemy::Draw(void)
{
	// �}�g���b�N�X�̐ݒ�
	SetMatrix();

	// �p���N���X�̕`��
	CMotion::Draw();
}

//=====================================================
// ���̓����蔻��̈ʒu�ݒ�
//=====================================================
void CEnemy::SetSpherePosition(D3DXVECTOR3 pos)
{
	if (m_pCollisionSphere != nullptr)
	{// �ʒu�ݒ�
		m_pCollisionSphere->SetPosition(pos);
	}
}