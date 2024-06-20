//*****************************************************
//
// �{�X�̃X�e�C�g�̏���[enemybossState.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "enemybossState.h"
#include "enemyboss.h"
#include "sound.h"
#include "manager.h"
#include "missile.h"
#include "universal.h"
#include "bullet.h"
#include "camera.h"
#include "cameraState.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const float MID_POINT = 2740.0f;	// �{�X��X�e�[�W�̒���X���W
const float FLOAT_HEIGHT = 180.0f;	// ������ł��鍂��
const float WIDTH_STAGE = 160.0f;	// �X�e�[�W�̕�
const float DELAY_MISSILE = 0.2f;	// �~�T�C�����˂̃f�B���C
const float INITIALSPEED_MISSILE = 3.0f;	// �~�T�C���̏���
const int NUM_MISSILE = 3;	// �~�T�C���̔��ː�
const float SHOT_HEIGHT = 30.0f;	// �ˌ����̍���
const float BULLET_SPEED = 2.0f;	// �e�̑��x
const float BULLET_SIZE = 2.5f;	// �e�̑傫��
const float DELAY_SHOT = 0.02f; // �ˌ��̃f�B���C
}

//************************************************************
// �o�����
//************************************************************
//=====================================================
// �R���X�g���N�^
//=====================================================
CEnemyBossStateApper::CEnemyBossStateApper()
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CEnemyBossStateApper::~CEnemyBossStateApper()
{

}

//=====================================================
// ����������
//=====================================================
void CEnemyBossStateApper::Init(CEnemyBoss *pBoss)
{
	// ���[�V�����ݒ�
	pBoss->SetMotion(CEnemyBoss::MOTION_APPER);
	pBoss->InitPose(CEnemyBoss::MOTION_APPER);

	// �o���n�_���킹
	pBoss->SetMatrix();

	pBoss->FollowCollision();
}

//=====================================================
// �X�V
//=====================================================
void CEnemyBossStateApper::Update(CEnemyBoss *pBoss)
{
	bool bFinish = pBoss->IsFinish();

	if (bFinish)
	{
		pBoss->SwitchState();

		// �J�������{�X��ɐ؂�ւ�
		CCamera *pCamera = Manager::GetCamera();

		if (pCamera != nullptr)
		{
			pCamera->ChangeState(new CCameraStateBossBattle);
		}
	}
}

//************************************************************
// �ˌ��U��
//************************************************************
//=====================================================
// �R���X�g���N�^
//=====================================================
CEnemyBossStateShot::CEnemyBossStateShot() : m_fTimerAttack(0.0f)
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CEnemyBossStateShot::~CEnemyBossStateShot()
{

}

//=====================================================
// ����������
//=====================================================
void CEnemyBossStateShot::Init(CEnemyBoss *pBoss)
{
	int nRand = rand() % 2;

	if (nRand == 1)
	{
		pBoss->SetMotion(CEnemyBoss::MOTION_SHOT_UPPER);
	}
	else
	{
		pBoss->SetMotion(CEnemyBoss::MOTION_SHOT_UNDER);
	}

	D3DXVECTOR3 pos = pBoss->GetPosition();

	D3DXVECTOR3 posDest;

	if (pos.x < MID_POINT)
	{// ���ɂ����ꍇ
		posDest = { MID_POINT - WIDTH_STAGE, FLOAT_HEIGHT + SHOT_HEIGHT, 0.0f };
	}
	else
	{
		posDest = { MID_POINT + WIDTH_STAGE, FLOAT_HEIGHT + SHOT_HEIGHT, 0.0f };
	}

	pBoss->SetPosDest(posDest);
}

//=====================================================
// �X�V
//=====================================================
void CEnemyBossStateShot::Update(CEnemyBoss *pBoss)
{
	pBoss->RotDest();

	pBoss->FollowDest();

	bool bFinish = pBoss->IsFinish();
	int nKey = pBoss->GetKey();

	if (nKey == 3)
	{
		m_fTimerAttack += Manager::GetDeltaTime();

		if (m_fTimerAttack >= DELAY_SHOT)
		{
			D3DXMATRIX mtxWeapon = *pBoss->GetParts(CEnemyBoss::IDX_WEAPON)->m_pParts->GetMatrix();
			D3DXMATRIX mtxMazzle;
			D3DXMATRIX mtxMazzleVec;

			// �I�t�Z�b�g�̈ʒu�ݒ�
			universal::SetOffSet(&mtxMazzle, mtxWeapon, D3DXVECTOR3(5.0f, -30.0f, 0.0f));
			universal::SetOffSet(&mtxMazzleVec, mtxMazzle, D3DXVECTOR3(0.0f, -1.0f, 0.0f));

			// �����̃x�N�g�����擾
			D3DXVECTOR3 posMazzle =
			{
				mtxMazzle._41,
				mtxMazzle._42,
				mtxMazzle._43,
			};
			D3DXVECTOR3 posBullet =
			{
				mtxMazzleVec._41,
				mtxMazzleVec._42,
				mtxMazzleVec._43,
			};

			D3DXVECTOR3 vecBullet = posBullet - posMazzle;

			D3DXVec3Normalize(&vecBullet, &vecBullet);

			vecBullet *= BULLET_SPEED;

			CBullet::Create(posMazzle, vecBullet, 400, CBullet::TYPE_ENEMY, false, 10.0f, 5.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

			m_fTimerAttack = 0;

			CSound *pSound = CSound::GetInstance();

			if (pSound != nullptr)
			{
				pSound->Play(CSound::LABEL_SE_BULLET);
			}
		}
	}

	if (bFinish)
	{// ��Ԑ؂�ւ�
		// �ڕW�ʒu�Ǐ]
		pBoss->SwitchState();
	}
}

//************************************************************
// �~�T�C���U��
//************************************************************
//=====================================================
// �R���X�g���N�^
//=====================================================
CEnemyBossStateMissile::CEnemyBossStateMissile() : m_fTimerAttack(0.0f), m_nCntAttack(0)
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CEnemyBossStateMissile::~CEnemyBossStateMissile()
{

}

//=====================================================
// ����������
//=====================================================
void CEnemyBossStateMissile::Init(CEnemyBoss *pBoss)
{
	pBoss->SetMotion(CEnemyBoss::MOTION_MISSILE);
}

//=====================================================
// �X�V
//=====================================================
void CEnemyBossStateMissile::Update(CEnemyBoss *pBoss)
{
	D3DXVECTOR3 pos = pBoss->GetPosition();

	// �v���C���[�̕�����������
	pBoss->RotDest();

	// �ڕW�ʒu�̐ݒ菈��
	D3DXVECTOR3 posDest;

	if (pos.x < MID_POINT)
	{// ���ɂ����ꍇ
		posDest = { MID_POINT - WIDTH_STAGE, FLOAT_HEIGHT, 0.0f };
	}
	else
	{
		posDest = { MID_POINT + WIDTH_STAGE, FLOAT_HEIGHT, 0.0f };
	}

	pBoss->SetPosDest(posDest);
	
	bool bArrival = pBoss->FollowDest();	// �ڕW�ʒu�Ǐ]

	// �~�T�C���𔭎˂���
	if (bArrival)
	{// �ڕW�n�_�ɒ����Ă�����U������
		m_fTimerAttack += Manager::GetDeltaTime();

		if (DELAY_MISSILE <= m_fTimerAttack)
		{// ��莞�Ԃ��ƂɃ~�T�C���𔭎�
			// �~�T�C���̐���
			D3DXVECTOR3 posMissile = pBoss->GetMtxPos(CEnemyBoss::IDX_SHOULDER_L);
			CMissile *pMissile = CMissile::Create(posMissile);

			if (pMissile != nullptr)
			{
				// �~�T�C���ɏ�����^����
				pMissile->SetMove(D3DXVECTOR3(0.0f, INITIALSPEED_MISSILE, 0.0f));
			}

			// ���ˉ��Đ�
			Sound::Play(CSound::LABEL_SE_MISSILE);

			m_fTimerAttack = 0;	// �^�C�}�[�̃��Z�b�g
			m_nCntAttack++;	// �J�E���^�[�̉��Z

			if (m_nCntAttack >= NUM_MISSILE)
			{// ��Ԃ�؂�ւ���
				pBoss->SwitchState();
			}
		}
	}
}

//************************************************************
// �ːi�U��
//************************************************************
//=====================================================
// �R���X�g���N�^
//=====================================================
CEnemyBossStateDash::CEnemyBossStateDash()
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CEnemyBossStateDash::~CEnemyBossStateDash()
{

}

//=====================================================
// ����������
//=====================================================
void CEnemyBossStateDash::Init(CEnemyBoss *pBoss)
{
	pBoss->SetMotion(CEnemyBoss::MOTION_DASH);

	D3DXVECTOR3 pos = pBoss->GetPosition();

	D3DXVECTOR3 posDest;

	if (pos.x < MID_POINT)
	{// ���ɂ����ꍇ
		posDest = { MID_POINT + WIDTH_STAGE, FLOAT_HEIGHT, 0.0f };
	}
	else
	{// �E�ɂ����ꍇ
		posDest = { MID_POINT - WIDTH_STAGE, FLOAT_HEIGHT, 0.0f };
	}

	pBoss->SetPosDest(posDest);
}

//=====================================================
// �X�V
//=====================================================
void CEnemyBossStateDash::Update(CEnemyBoss *pBoss)
{
	bool bFinish = pBoss->IsFinish();

	if (bFinish)
	{// ��Ԑ؂�ւ�
		// �ڕW�ʒu�Ǐ]
		bool bEnd = pBoss->FollowDest();

		if (bEnd)
		{
			pBoss->SwitchState();
		}
	}
	else
	{
		pBoss->RotDest();
	}
}