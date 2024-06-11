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
// �萔��`
//*****************************************************
namespace
{
const int INITIAL_LIFE = 5;	// �����̗�
const int INITIAL_SCORE = 500;	// �����X�R�A
const float DELAY_SHOT = 2.0f;	// �ˌ��J�E���^�[
const float BULLET_SPEED = 2.0f;	// �e�̑��x
const float BULLET_SIZE = 1.0f;	// �e�̑傫��
const float DIST_ATTACK = 200.0f;	// �U������͈�
}

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
	if (GetAttackCounter() >= DELAY_SHOT)
	{// ��莞�Ԍo�߂�����U��
		D3DXVECTOR3 pos = GetPosition();
		D3DXVECTOR3 posTarget = { 0.0f,0.0f,0.0f };
		float fRot = GetRot().y;
		D3DXVECTOR3 move;

		CPlayer *pPlayer = CPlayer::GetInstance();

		if (pPlayer != nullptr)
		{
			// �v���C���[�̍��p�[�c��ڕW�ɂ���
			CMotion *pMotion = pPlayer->GetBody();
			posTarget = pMotion->GetMtxPos(0);

			// �����x�N�g���̐��K���������̂�e�̈ړ��ʂɂ���
			move = posTarget - pos;

			float fLength = D3DXVec3Length(&move);

			if (fLength > DIST_ATTACK)
			{// ��苗���ȓ��łȂ��ƍU�����Ȃ�
				return;
			}

			D3DXVec3Normalize(&move, &move);

			move *= BULLET_SPEED;
		}

		// �e�̐���
		CBullet::Create(pos, move, 500, CBullet::TYPE_ENEMY, false, BULLET_SIZE, 2.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

		SetAttackCounter(0);
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CEnemyDrone::Draw(void)
{
	CEnemyNormal::Draw();
}