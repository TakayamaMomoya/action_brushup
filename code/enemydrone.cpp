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
#include "enemydrone.h"
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
#define TIME_SHOT	(120)	// �ˌ��܂ł̃J�E���^�[
#define BULLET_SPEED	(2.0f)	// �e�̑��x
#define BULLET_SIZE	(1.0f)	// �e�̑傫��
#define GRAVITY	(0.3f)	// �d��

//=====================================================
// �R���X�g���N�^
//=====================================================
CEnemyDrone::CEnemyDrone()
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CEnemyDrone::~CEnemyDrone()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CEnemyDrone::Init(void)
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
void CEnemyDrone::Uninit(void)
{
	// �p���N���X�̏I��
	CEnemyNormal::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CEnemyDrone::Update(void)
{
	// �ʒu��ۑ�
	SetPositionOld(GetPosition());

	// �p���N���X�̍X�V
	CEnemyNormal::Update();
	
	// �U���̊Ǘ�
	ManageAttack();

	// �ڕW����������
	RotDest();
}

//=====================================================
// �U���Ǘ�
//=====================================================
void CEnemyDrone::ManageAttack(void)
{
	if (GetAttackCounter() >= TIME_SHOT)
	{// �U��
		D3DXVECTOR3 pos = GetPosition();
		D3DXVECTOR3 posTarget = { 0.0f,0.0f,0.0f };
		float fRot = GetRot().y;
		D3DXVECTOR3 move;

		// �ڕW�ʒu�擾
		CPlayer *pPlayer = CPlayer::GetInstance();

		if (pPlayer != nullptr)
		{
			CMotion *pMotion = pPlayer->GetBody();

			posTarget = pMotion->GetMtxPos(0);

			move = posTarget - pos;

			float fLength = D3DXVec3Length(&move);

			if (fLength > 200.0f)
			{
				return;
			}

			D3DXVec3Normalize(&move, &move);

			move *= BULLET_SPEED;
		}

		CBullet::Create(pos, move, 500, CBullet::TYPE_ENEMY, false, BULLET_SIZE, 2.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

		SetAttackCounter(0);
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CEnemyDrone::Draw(void)
{
	// �p���N���X�̕`��
	CEnemyNormal::Draw();
}