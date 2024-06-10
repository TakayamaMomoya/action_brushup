//*****************************************************
//
// �J�����̏���[camera.h]
// Author:���R����
//
//*****************************************************
#ifndef _CAMERA_H_	// ��d�C���N���[�h�h�~
#define _CAMERA_H_

//****************************************************
// �C���N���[�h
//****************************************************
#include "main.h"

//****************************************************
// �}�N����`
//****************************************************
#define MIN_DRAW		(10.0f)					// �`����J�n���鋗��
#define MAX_DRAW		(700000.0f)				// �`����I�����鋗��

//****************************************************
// �O���錾
//****************************************************
class CCameraState;

//****************************************************
// �N���X�̒�`
//****************************************************
class CCamera
{
public:
	// �\���̐錾
	struct S_InfoCamera
	{// �J�����̏��
		D3DXVECTOR3 posV;	// ���_
		D3DXVECTOR3 posVOld;	// ���_�̑O��̈ʒu
		D3DXVECTOR3 posR;	// �����_
		D3DXVECTOR3 posVDest;	// �ړI�̎��_
		D3DXVECTOR3 posRDest;	// �ړI�̒����_
		D3DXVECTOR3 vecU;	// ������x�N�g��
		D3DXVECTOR3 rot;	// ����
		float fViewAngle;	// ����p
		float fLength;	// ���_���璍���_�܂ł̋���
		D3DXMATRIX mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
		D3DXMATRIX mtxView;	// �r���[�}�g���b�N�X
		int nTimerQuake;	// �U���̃^�C�}�[
		float fQuakeSize;

		// �R���X�g���N�^
		S_InfoCamera() : posV{}, posVOld{}, posR{}, posVDest{}, posRDest{}, vecU{}, rot{}, fViewAngle(0.0f),
			fLength(0.0f), mtxProjection(), mtxView(), nTimerQuake(0), fQuakeSize(0.0f) {};
	};

	CCamera();	// �R���X�g���N�^
	~CCamera();	// �f�X�g���N�^

	// �����o�ϐ�
	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void SetCamera(void);	// �J�����̃Z�b�g
	void SetPosV(void);	// ���_�ʒu�̐ݒ�
	void SetPosR(void);	// �����_�ʒu�̐ݒ�
	void SetQuake(float fQuakeSize, int nTime);	// �U���ݒ�
	void Quake(void);	// �U�����̏���

	// �ϐ��擾�E�ݒ�֐�
	void SetDist(float fDist) { m_camera.fLength = fDist; }	// �J��������
	float GetDist(void) { return m_camera.fLength; }
	S_InfoCamera *GetInfo(void);	// ���\����
	void ChangeState(CCameraState *pBehavior);	// �X�e�C�g�ύX

private:
	// �����o�֐�
	void Debug(void);	// �f�o�b�O����

	// �����o�֐�
	S_InfoCamera m_camera;	// �\���̂̏��
	CCameraState *m_pState;	// �X�e�C�g
};

#endif