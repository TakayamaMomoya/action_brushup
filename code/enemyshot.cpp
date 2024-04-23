//*****************************************************
//
// �����G�̏���[enemyshot.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "enemyshot.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "universal.h"
#include "debugproc.h"
#include "game.h"
#include "bullet.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define INITIAL_LIFE	(5)	// �����̗�
#define INITIAL_SCORE	(500)	// �����X�R�A
#define TIME_SHOT	(240)	// �ˌ��܂ł̃J�E���^�[
#define ROLL_FACT	(0.1f)	// ��]�W��
#define BULLET_SPEED	(2.0f)	// �e�̑��x
#define BULLET_SIZE	(2.5f)	// �e�̑傫��
#define GRAVITY	(0.3f)	// �d��

//=====================================================
// �R���X�g���N�^
//=====================================================
CEnemyShot::CEnemyShot()
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CEnemyShot::~CEnemyShot()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CEnemyShot::Init(void)
{
	// �p���N���X�̏�����
	CEnemyNormal::Init();

	// �����̗̑͐ݒ�
	SetLife(INITIAL_LIFE);

	// �X�R�A�ݒ�
	SetScore(INITIAL_SCORE);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CEnemyShot::Uninit(void)
{
	// �p���N���X�̏I��
	CEnemyNormal::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CEnemyShot::Update(void)
{
	// �ʒu��ۑ�
	SetPositionOld(GetPosition());

	// �p���N���X�̍X�V
	CEnemyNormal::Update();
	
	// �U���̊Ǘ�
	ManageAttack();

	// �ڕW����������
	RotDest();

	// �d��
	D3DXVECTOR3 move = GetMove();

	move.y -= GRAVITY;

	SetMove(move);
}

//=====================================================
// �U���Ǘ�
//=====================================================
void CEnemyShot::ManageAttack(void)
{
	int nMotion = GetMotion();
	int nFrame = GetFrame();
	int nKey = GetKey();

	if (GetAttackCounter() >= TIME_SHOT && nMotion != MOTION_SHOT)
	{// �ˌ����[�V����
		SetMotion(MOTION_SHOT);
	}

	if (nMotion == MOTION_SHOT && 
		nFrame == 0 &&
		nKey == 2)
	{// �w��̃^�C�~���O�Œe������
		D3DXVECTOR3 pos = GetPosition();
		float fRot = GetRot().y;
		D3DXVECTOR3 move;

		pos.y += 10.0f;

		move =
		{
			sinf(fRot) * BULLET_SPEED,
			0.0f,
			cosf(fRot) * BULLET_SPEED
		};

		// �ڕW�ʒu�擾
		CPlayer *pPlayer = CPlayer::GetInstance();

		if (pPlayer != nullptr)
		{
			D3DXVECTOR3 posTarget = pPlayer->GetPosition();

			D3DXVECTOR3 vecDiff = posTarget - pos;

			float fLength = D3DXVec3Length(&vecDiff);

			if (fLength > 250.0f)
			{
				return;
			}
		}

		CBullet::Create(pos, -move, 500, CBullet::TYPE_ENEMY,false,BULLET_SIZE, 2.0f,D3DXCOLOR(1.0f,0.0f,0.0f,1.0f));

		SetAttackCounter(0);
	}

	if (nMotion == MOTION_SHOT &&
		IsFinish())
	{// �ˌ����[�V�����̏I��
		SetMotion(MOTION_NEUTRAL);
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CEnemyShot::Draw(void)
{
	// �p���N���X�̕`��
	CEnemyNormal::Draw();
}