//*****************************************************
//
// �c���̏���[afterimage.cpp]
// Author:���R����
//
//*****************************************************
#ifndef _AFTERIMAGE_H_	// ��d�C���N���[�h�h�~
#define _AFTERIMAGE_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "ObjectX.h"

//*****************************************************
// �O���錾
//*****************************************************
class CCollisionCube;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CAfterImage : public CObjectX
{
public:
	CAfterImage(int nPriority = 6);	// �R���X�g���N�^
	~CAfterImage();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��

	// �ÓI�����o�֐�
	static CAfterImage *Create(D3DXMATRIX mtx, int nIdxModel, D3DXCOLOR col, int m_nLife);	// ��������

private:
	// �����o�ϐ�
	int m_nLife;	// �̗�
	float m_fDecAlpha;	// �����x������

	// �ÓI�����o�ϐ�
	static int s_nNumAll;	// ����
};

#endif
