//******************************************
//
// �O�Ղ̏���(orbit.h)
// Author:���R����
//
//******************************************
#ifndef _ORBIT_H_	// ��d�C���N���[�h�h�~
#define _ORBIT_H_

//******************************************
// �C���N���[�h
//******************************************
#include "object.h"

//******************************************
// �萔��`
//******************************************
namespace Orbit
{
const int MAX_EDGE = 500;	// �ӂ̍ő吔
const int NUM_OFFSET = 2;	// �I�t�Z�b�g�̐�
}

//******************************************
// �N���X��`
//******************************************
class COrbit : public CObject
{
public:
	COrbit(int nPriority = 6);	// �R���X�g���N�^
	~COrbit();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void); // ������
	void Uninit(void);  // �I��
	void Update(void);  // �X�V
	void Draw(void);  // �`��
	void SetPositionOffset(D3DXMATRIX mtxWorld, int nIdxOrbit);	// �I�t�Z�b�g�̈ʒu��ݒ�
	
	// �ϐ��擾�E�ݒ�֐�
	bool IsEnd(void) { return m_bEnd; }	// �؂藣���t���O
	void SetEnd(bool bEnd) { m_bEnd = bEnd; }

	// �ÓI�����o�֐�
	static COrbit *Create(D3DXMATRIX mtxWorld, D3DXVECTOR3 posOffset1, D3DXVECTOR3 posOffset2, D3DXCOLOR col, int nNumEdge);	// ��������

private:
	// �����o�֐�
	void UpdatePolygon(void);	// �|���S���̍X�V

	// �����o�ϐ�
	int m_nIdxTexture;	// �e�N�X�`���ԍ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;		// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_aPosOffset[Orbit::NUM_OFFSET];	// �I�t�Z�b�g�ʒu
	D3DXVECTOR3 m_aPosPoint[Orbit::MAX_EDGE][Orbit::NUM_OFFSET];	// ���_���W�ۑ��p
	D3DXCOLOR m_col;	// �F
	D3DXCOLOR m_aColPoint[Orbit::MAX_EDGE][Orbit::NUM_OFFSET];	// ���_�J���[�ۑ��p
	D3DXMATRIX m_aMtxOffset[Orbit::NUM_OFFSET];	// �I�t�Z�b�g�̃}�g���b�N�X
	int m_nNumEdge;	//�ӂ̐�
	int m_nID;	// �ԍ�
	bool m_bEnd;	// �I�����Ă邩�ǂ���
};

#endif