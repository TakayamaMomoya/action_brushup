//*****************************************************
//
// �J�����̃X�e�C�g[cameraState.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "cameraState.h"
#include "camera.h"
#include "player.h"
#include "motion.h"
#include "player.h"
#include "enemyboss.h"
#include "universal.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const float ANGLE_FOLLOW = D3DX_PI * 0.4f;	// �Ǐ]���̊p�x
const float SPEED_FOLLOW = 0.3f;	// �Ǐ]���̑��x
const float RATE_ADVANCE_FOLLOW = 10.0f;	// �Ǐ]���A�ړ��ʂɑ΂��������銄��
const float DIST_FOLLOW_DEFAULT = 100.0f;	// �Ǐ]���̃f�t�H���g�J��������
const float DIST_APPER_PLAYER = 100.0f;	// �v���C���[�o�����̃J��������
const float DIST_MIN_BOSS = 85.0f;	// �{�X��̂Ƃ��̍ŏ�����
const D3DXVECTOR3 INITIAL_ROT_FOLLOWPLAYER = { 1.0f,0.0f,0.0f };	// �v���C���[�Ǐ]�̏����p�x
}

//====================================================
// �R���X�g���N�^
//====================================================
CCameraState::CCameraState()
{

}

//====================================================
// �f�X�g���N�^
//====================================================
CCameraState::~CCameraState()
{

}

//************************************************************
// �^�C�g��
//************************************************************
//====================================================
// �R���X�g���N�^
//====================================================
CCameraStateTitle::CCameraStateTitle()
{

}

//====================================================
// �f�X�g���N�^
//====================================================
CCameraStateTitle::~CCameraStateTitle()
{

}

//====================================================
// ������
//====================================================
void CCameraStateTitle::Init(CCamera *pCamera)
{
	D3DXVECTOR3 posV = { -1.29f,43.68f,475.58f };
	D3DXVECTOR3 posR = { 106.19f,-62.93f,-3.55f };

	pCamera->GetInfo()->posV = posV;
	pCamera->GetInfo()->posVDest = posV;
	
	pCamera->GetInfo()->posR = posR;
	pCamera->GetInfo()->posRDest = posR;
}

//====================================================
// �X�V����
//====================================================
void CCameraStateTitle::Update(CCamera *pCamera)
{

}

//************************************************************
// �v���C���[�Ǐ]
//************************************************************
//====================================================
// �R���X�g���N�^
//====================================================
CCameraStateFollowPlayer::CCameraStateFollowPlayer()
{

}

//====================================================
// �f�X�g���N�^
//====================================================
CCameraStateFollowPlayer::~CCameraStateFollowPlayer()
{

}

//====================================================
// ������
//====================================================
void CCameraStateFollowPlayer::Init(CCamera *pCamera)
{
	pCamera->GetInfo()->rot = INITIAL_ROT_FOLLOWPLAYER;
	pCamera->SetDist(DIST_FOLLOW_DEFAULT);
}

//====================================================
// �X�V����
//====================================================
void CCameraStateFollowPlayer::Update(CCamera *pCamera)
{
	// �J�����̐U��
	pCamera->Quake();

	// �v���C���[�擾
	CPlayer *pPlayer = CPlayer::GetInstance();

	if (pPlayer == nullptr)
	{
		return;
	}

	CCamera::S_InfoCamera *pInfoCamera = pCamera->GetInfo();
	D3DXVECTOR3 pos = pPlayer->GetPosition();
	D3DXVECTOR3 move = pPlayer->GetMove();

	// �����_�͉��݈̂ړ��������ǂ݂��ē���
	pInfoCamera->posRDest.x = pos.x + move.x * RATE_ADVANCE_FOLLOW;
	pInfoCamera->posRDest.z = pos.z + move.z * RATE_ADVANCE_FOLLOW;
	pInfoCamera->posRDest.y = pos.y;

	// �����_����̋ɍ��W�Ɏ��_��ݒ�
	pInfoCamera->posVDest =
	{
		pInfoCamera->posRDest.x + sinf(ANGLE_FOLLOW) * sinf(D3DX_PI) * pInfoCamera->fLength,
		pInfoCamera->posRDest.y + cosf(ANGLE_FOLLOW) * pInfoCamera->fLength,
		pInfoCamera->posRDest.z + sinf(ANGLE_FOLLOW) * cosf(D3DX_PI) * pInfoCamera->fLength
	};

	// �ʒu�̕␳
	pInfoCamera->posR += (pInfoCamera->posRDest - pInfoCamera->posR) * SPEED_FOLLOW;
	pInfoCamera->posV += (pInfoCamera->posVDest - pInfoCamera->posV) * SPEED_FOLLOW;
}

//************************************************************
// �v���C���[�o��
//************************************************************
//====================================================
// �R���X�g���N�^
//====================================================
CCameraStateApperPlayer::CCameraStateApperPlayer()
{

}

//====================================================
// �f�X�g���N�^
//====================================================
CCameraStateApperPlayer::~CCameraStateApperPlayer()
{

}

//====================================================
// ������
//====================================================
void CCameraStateApperPlayer::Init(CCamera *pCamera)
{
	pCamera->SetDist(DIST_APPER_PLAYER);
}

//====================================================
// �X�V����
//====================================================
void CCameraStateApperPlayer::Update(CCamera *pCamera)
{
	// �v���C���[�擾
	CPlayer *pPlayer = CPlayer::GetInstance();

	if (pPlayer == nullptr)
	{
		return;
	}

	CCamera::S_InfoCamera *pInfoCamera = pCamera->GetInfo();
	D3DXVECTOR3 pos = pPlayer->GetPosition();

	pInfoCamera->posR = pos;

	pInfoCamera->posV =
	{
		pInfoCamera->posRDest.x + sinf(ANGLE_FOLLOW) * sinf(D3DX_PI) * pInfoCamera->fLength,
		pInfoCamera->posRDest.y + cosf(ANGLE_FOLLOW) * pInfoCamera->fLength,
		pInfoCamera->posRDest.z + sinf(ANGLE_FOLLOW) * cosf(D3DX_PI) * pInfoCamera->fLength
	};
}

//************************************************************
// �{�X�펞�̓���
//************************************************************

//====================================================
// �R���X�g���N�^
//====================================================
CCameraStateBossBattle::CCameraStateBossBattle()
{

}

//====================================================
// �f�X�g���N�^
//====================================================
CCameraStateBossBattle::~CCameraStateBossBattle()
{

}

//====================================================
// ������
//====================================================
void CCameraStateBossBattle::Init(CCamera *pCamera)
{

}

//====================================================
// �X�V����
//====================================================
void CCameraStateBossBattle::Update(CCamera *pCamera)
{
	CPlayer *pPlayer = CPlayer::GetInstance();
	CEnemyBoss *pBoss = CEnemyBoss::GetInstance();

	if (pBoss == nullptr || pPlayer == nullptr)
		return;

	CMotion *pPlayerBody = pPlayer->GetBody();

	if (pPlayerBody == nullptr)
		return;

	// �{�X�ƃv���C���[�̒��S���f��
	D3DXVECTOR3 posPlayer = pPlayerBody->GetMtxPos(0);
	D3DXVECTOR3 posBoss = pBoss->GetMtxPos(CEnemyBoss::IDXPARTS::IDX_HEAD);

	D3DXVECTOR3 vecDiff = posBoss - posPlayer;

	D3DXVECTOR3 posMid = posPlayer + vecDiff * 0.5f;

	// �����_�𒆊Ԉʒu�ɐݒ�
	CCamera::S_InfoCamera *pInfoCamera = pCamera->GetInfo();
	
	pInfoCamera->posRDest = posMid;

	// �J�����̉�p���ɓ�̂����߂�
	float fAngleView = pInfoCamera->fViewAngle;

	float fAngle = (D3DX_PI - D3DXToRadian(fAngleView)) * 0.5f;	// �L�����N�^�[�Ԃ̃x�N�g���̒[����̊p�x

	float fLengthDiff = D3DXVec3Length(&vecDiff) * 0.5f;	// �v���C���[�ƓG�̋����̔���

	float fLengthToPosV = fLengthDiff / tanf(universal::DegreeToRadian(fAngleView * 0.5f));

	universal::LimitValue(&fLengthToPosV, FLT_MAX, DIST_MIN_BOSS);

	// �����_����̋ɍ��W�Ɏ��_��ݒ�
	pInfoCamera->posVDest =
	{
		pInfoCamera->posRDest.x + sinf(ANGLE_FOLLOW) * sinf(D3DX_PI) * fLengthToPosV,
		pInfoCamera->posRDest.y + cosf(ANGLE_FOLLOW) * fLengthToPosV,
		pInfoCamera->posRDest.z + sinf(ANGLE_FOLLOW) * cosf(D3DX_PI) * fLengthToPosV
	};

	// �ʒu�̕␳
	pInfoCamera->posR += (pInfoCamera->posRDest - pInfoCamera->posR) * SPEED_FOLLOW;
	pInfoCamera->posV += (pInfoCamera->posVDest - pInfoCamera->posV) * SPEED_FOLLOW;
}