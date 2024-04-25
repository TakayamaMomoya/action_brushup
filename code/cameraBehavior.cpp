//*****************************************************
//
// �J�����̃r�w�C�r�A[cameraBehavior.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "cameraBehavior.h"
#include "camera.h"
#include "player.h"
#include "motion.h"

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
}

//====================================================
// �R���X�g���N�^
//====================================================
CCameraBehavior::CCameraBehavior()
{

}

//====================================================
// �f�X�g���N�^
//====================================================
CCameraBehavior::~CCameraBehavior()
{

}

//************************************************************
// �v���C���[�Ǐ]
//************************************************************

//====================================================
// �R���X�g���N�^
//====================================================
CCameraBehaviorFollowPlayer::CCameraBehaviorFollowPlayer()
{

}

//====================================================
// �f�X�g���N�^
//====================================================
CCameraBehaviorFollowPlayer::~CCameraBehaviorFollowPlayer()
{

}

//====================================================
// ������
//====================================================
void CCameraBehaviorFollowPlayer::Init(CCamera *pCamera)
{
	pCamera->SetDist(DIST_FOLLOW_DEFAULT);
}

//====================================================
// �X�V����
//====================================================
void CCameraBehaviorFollowPlayer::Update(CCamera *pCamera)
{
	// �J�����̐U��
	pCamera->Quake();

	// �v���C���[�擾
	CPlayer *pPlayer = CPlayer::GetInstance();

	if (pPlayer == nullptr)
	{
		return;
	}

	CCamera::Camera *pInfoCamera = pCamera->GetCamera();
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
CCameraBehaviorApperPlayer::CCameraBehaviorApperPlayer()
{

}

//====================================================
// �f�X�g���N�^
//====================================================
CCameraBehaviorApperPlayer::~CCameraBehaviorApperPlayer()
{

}

//====================================================
// ������
//====================================================
void CCameraBehaviorApperPlayer::Init(CCamera *pCamera)
{
	pCamera->SetDist(DIST_APPER_PLAYER);
}

//====================================================
// �X�V����
//====================================================
void CCameraBehaviorApperPlayer::Update(CCamera *pCamera)
{
	// �v���C���[�擾
	CPlayer *pPlayer = CPlayer::GetInstance();

	if (pPlayer == nullptr)
	{
		return;
	}

	CCamera::Camera *pInfoCamera = pCamera->GetCamera();
	D3DXVECTOR3 pos = pPlayer->GetPosition();

	pInfoCamera->posR = pos;

	pInfoCamera->posV =
	{
		pInfoCamera->posRDest.x + sinf(ANGLE_FOLLOW) * sinf(D3DX_PI) * pInfoCamera->fLength,
		pInfoCamera->posRDest.y + cosf(ANGLE_FOLLOW) * pInfoCamera->fLength,
		pInfoCamera->posRDest.z + sinf(ANGLE_FOLLOW) * cosf(D3DX_PI) * pInfoCamera->fLength
	};
}