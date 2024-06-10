//*****************************************************
//
// �J�����̏���[camera.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "manager.h"
#include "renderer.h"
#include "main.h"
#include "camera.h"
#include "inputkeyboard.h"
#include "inputmouse.h"
#include "debugproc.h"
#include "game.h"
#include "player.h"
#include "cameraState.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const float INITIAL_FOV = 45.0f;	// �����̎���p
const float DECREASE_QUAKE = 0.03f;	// �h��̎��܂鑬�x
const int RATE_FLOAT = 100;	// float�^�̔{��
}

//====================================================
// �R���X�g���N�^
//====================================================
CCamera::CCamera()
{
	ZeroMemory(&m_camera, sizeof(S_InfoCamera));
	m_pState = nullptr;
}

//====================================================
// �f�X�g���N�^
//====================================================
CCamera::~CCamera()
{

}

//====================================================
// ����������
//====================================================
HRESULT CCamera::Init(void)
{
	m_camera.fViewAngle = INITIAL_FOV;
	m_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	return S_OK;
}

//====================================================
// �I������
//====================================================
void CCamera::Uninit(void)
{

}

//====================================================
// �X�V����
//====================================================
void CCamera::Update(void)
{
	if (m_pState != nullptr)
	{
		m_pState->Update(this);
	}
}

//====================================================
// �f�o�b�O����
//====================================================
void CCamera::Debug(void)
{

}

//====================================================
// �U������
//====================================================
void CCamera::Quake(void)
{
	// ��ʐU��
	if (m_camera.nTimerQuake > 0)
	{
		// ���Ԃ����炷
		m_camera.nTimerQuake--;

		// ���_�����_�𓮂����ăJ������h�炷
		m_camera.posV.x += (float)(rand() % RATE_FLOAT) / (float)RATE_FLOAT * m_camera.fQuakeSize * sinf(m_camera.rot.y);
		m_camera.posV.y += (float)(rand() % RATE_FLOAT) / (float)RATE_FLOAT * m_camera.fQuakeSize;
		m_camera.posV.z += (float)(rand() % RATE_FLOAT) / (float)RATE_FLOAT * m_camera.fQuakeSize * cosf(m_camera.rot.y);

		m_camera.posR.x += (float)(rand() % RATE_FLOAT) / (float)RATE_FLOAT * m_camera.fQuakeSize * sinf(m_camera.rot.y);
		m_camera.posR.y += (float)(rand() % RATE_FLOAT) / (float)RATE_FLOAT * m_camera.fQuakeSize;
		m_camera.posR.z += (float)(rand() % RATE_FLOAT) / (float)RATE_FLOAT * m_camera.fQuakeSize * cosf(m_camera.rot.y);

		// ���X�ɗh��̃T�C�Y������������
		m_camera.fQuakeSize += (0.0f - m_camera.fQuakeSize) * DECREASE_QUAKE;
	}
}

//====================================================
// �U���ݒ�
//====================================================
void CCamera::SetQuake(float fQuakeSize, int nTime)
{
	if (fQuakeSize > 0.0f)
	{
		// �h��鎞�ԑ��
		m_camera.nTimerQuake = nTime;

		// �h��̑傫�����
		m_camera.fQuakeSize = fQuakeSize;
	}
}

//====================================================
// ���_�ݒ�
//====================================================
void CCamera::SetPosV(void)
{
	m_camera.posV =
	{
		m_camera.posR.x + sinf(m_camera.rot.x) * sinf(m_camera.rot.y) * m_camera.fLength,
		m_camera.posR.y + cosf(m_camera.rot.x) * m_camera.fLength,
		m_camera.posR.z + sinf(m_camera.rot.x) * cosf(m_camera.rot.y) * m_camera.fLength
	};
}

//====================================================
// �����_�ݒ�
//====================================================
void CCamera::SetPosR(void)
{
	m_camera.posR =
	{
		m_camera.posV.x - sinf(m_camera.rot.x) * sinf(m_camera.rot.y) * m_camera.fLength,
		m_camera.posV.y - cosf(m_camera.rot.x) * m_camera.fLength,
		m_camera.posV.z - sinf(m_camera.rot.x) * cosf(m_camera.rot.y) * m_camera.fLength
	};
}

//====================================================
// �ݒ菈��
//====================================================
void CCamera::SetCamera(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	// �v���W�F�N�V�����}�g���b�N�X������
	D3DXMatrixIdentity(&m_camera.mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�쐬
	D3DXMatrixPerspectiveFovLH(&m_camera.mtxProjection,
		D3DXToRadian(m_camera.fViewAngle),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		MIN_DRAW,
		MAX_DRAW);

	// �v���W�F�N�V�����}�g���b�N�X�ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION,&m_camera.mtxProjection);

	// �r���[�}�g���b�N�X������
	D3DXMatrixIdentity(&m_camera.mtxView);

	// �r���[�}�g���b�N�X�쐬
	D3DXMatrixLookAtLH(&m_camera.mtxView,
		&m_camera.posV,
		&m_camera.posR,
		&m_camera.vecU);

	// �r���[�}�g���b�N�X�ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_camera.mtxView);

#ifdef _DEBUG	// �f�o�b�O�\��
	CDebugProc::GetInstance()->Print("\n���_�̈ʒu�F[%f,%f,%f]", m_camera.posV.x, m_camera.posV.y, m_camera.posV.z);
	CDebugProc::GetInstance()->Print("\n�����_�̈ʒu�F[%f,%f,%f]", m_camera.posR.x, m_camera.posR.y, m_camera.posR.z);
	CDebugProc::GetInstance()->Print("\n�J���������F[%f]", m_camera.fLength);
#endif
}

//====================================================
// �X�e�C�g�̕ύX
//====================================================
void CCamera::ChangeState(CCameraState *pBehavior)
{
	if (m_pState != nullptr)
	{
		delete m_pState;
		m_pState = nullptr;
	}

	m_pState = pBehavior;

	if (m_pState != nullptr)
	{
		m_pState->Init(this);
	}
}

//====================================================
// ���擾
//====================================================
CCamera::S_InfoCamera *CCamera::GetInfo(void)
{
	return &m_camera;
}