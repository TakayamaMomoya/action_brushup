//*****************************************************
//
// �ʏ�G�̏���[enemyNormal.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "enemyNormal.h"
#include "manager.h"
#include "score.h"
#include "collision.h"
#include "debugproc.h"
#include "particle.h"
#include <stdio.h>
#include "player.h"
#include "game.h"
#include "enemyManager.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define SPEED_MOVE	(1.0f)	// �ړ����x
#define RATE_RADIUS	(1.5f)	// �����蔻��̑傫���̔{��
#define INITIAL_LIFE	(5.0f)	// �����̗�
#define DAMAGE_FRAME	(10)	// �_���[�W��Ԃ̌p���t���[����
#define INITIAL_SCORE	(1000)	// �����X�R�A
#define TIME_DEATH	(30)	// ���S�܂ł̃^�C��

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
int CEnemyNormal::m_nNumAll = 0;	// ����

//=====================================================
// �R���X�g���N�^
//=====================================================
CEnemyNormal::CEnemyNormal()
{
	// �����J�E���g�A�b�v
	m_nNumAll++;

	// �l�̃N���A
	m_fLife = 0;
	m_nScore = 0;
	m_nCntAttack = 0;
	m_nTimerState = 0;
	m_pCollisionSphere = nullptr;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CEnemyNormal::~CEnemyNormal()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CEnemyNormal::Init(void)
{
	// �ł��傫���p�[�c�̔��a�擾
	float fRadius = GetRadiusMax();

	// �p���N���X�̏�����
	CEnemy::Init();

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

	m_nScore = INITIAL_SCORE;

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CEnemyNormal::Uninit(void)
{
	if (m_pCollisionSphere != nullptr)
	{// �����蔻��̏���
		m_pCollisionSphere->Uninit();

		m_pCollisionSphere = nullptr;
	}

	if (m_pCollisionCube == nullptr)
	{// �����̂̓����蔻��
		m_pCollisionCube->Uninit();

		m_pCollisionCube = nullptr;
	}

	// �p���N���X�̏I��
	CEnemy::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CEnemyNormal::Update(void)
{
	CEnemy::STATE state = GetState();

	if (state != STATE_DEATH)
	{
		m_nCntAttack++;

		if (m_nCntAttack == INT_MAX)
		{
			m_nCntAttack = 0;
		}

		// �p���N���X�̍X�V
		CEnemy::Update();
	}

	// ��ԊǗ�����
	ManageState();

	// �ʒu�̍X�V
	SetPosition(GetPosition() + GetMove());

	// �����蔻��Ǘ�
	ManageCollision();
}

//=====================================================
// �����蔻��̊Ǘ�
//=====================================================
void CEnemyNormal::ManageCollision(void)
{
	if (m_pCollisionSphere != nullptr)
	{// ���̓����蔻��̊Ǘ�
		m_pCollisionSphere->SetPositionOld(m_pCollisionSphere->GetPosition());

		m_pCollisionSphere->SetPosition(GetPosition());
	}

	if (m_pCollisionCube != nullptr)
	{// �����̂̓����蔻��̊Ǘ�
	 // �p�[�c�̍ő唼�a�擾
		float fRadius = GetRadiusMax();

		// �����蔻��̈ʒu�ݒ�
		m_pCollisionCube->SetPosition(GetPosition());

		D3DXVECTOR3 vtxMax = { fRadius,fRadius,fRadius };
		D3DXVECTOR3 vtxMin = { -fRadius,10.0f,-fRadius };

		D3DXVECTOR3 move = GetMove();

		// �����o���̓����蔻��
		m_pCollisionCube->CubeCollision(CCollision::TAG_BLOCK, &move);

		SetMove(move);
	}
}

//=====================================================
// ��ԊǗ�
//=====================================================
void CEnemyNormal::ManageState(void)
{
	CEnemy::STATE state = GetState();

	D3DXCOLOR col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	switch (state)
	{
	case STATE_NORMAL:
		break;
	case STATE_DAMAGE:
		if (m_nTimerState > DAMAGE_FRAME)
		{// �ʏ��Ԃɖ߂�
			m_nTimerState = 0;
			state = STATE_NORMAL;
		}
		else
		{// �J�E���g�A�b�v
			m_nTimerState++;
		}

		break;
	case STATE_DEATH:

		m_nTimerState++;

		// �����ɂȂ�Ȃ��������
		col = D3DXCOLOR(1.0f,0.0f,0.0f,1.0f);

		col.a = 1.0f - (float)((float)(m_nTimerState) / (TIME_DEATH));

		SetAllCol(col);

		if (m_nTimerState >= TIME_DEATH)
		{// ���S
			Death();
		}

		break;
	default:
		break;
	}

	// ��Ԑݒ�
	SetState(state);
}

//=====================================================
// ���S����
//=====================================================
void CEnemyNormal::Death(void)
{
	// ���g�̏I��
	Uninit();
}

//=====================================================
// �`�揈��
//=====================================================
void CEnemyNormal::Draw(void)
{
	// �p���N���X�̕`��
	CEnemy::Draw();
}

//=====================================================
// ���̓����蔻��̈ʒu�ݒ�
//=====================================================
void CEnemyNormal::SetSpherePosition(D3DXVECTOR3 pos)
{
	if (m_pCollisionSphere != nullptr)
	{// �ʒu�ݒ�
		m_pCollisionSphere->SetPosition(pos);
	}
}