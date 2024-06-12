//*****************************************************
//
// 2D�|���S���̏���[object2D.h]
// Author:���R����
//
//*****************************************************
#ifndef _OBJECT2D_H_	// ��d�C���N���[�h�h�~
#define _OBJECT2D_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "object.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CObject2D	: public CObject
{
public:
	CObject2D(int nPriority = 3);	// �R���X�g���N�^
	~CObject2D();	//	�f�X�g���N�^

	// �����o�ϐ�
	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��
	void SetVtx(void);	// ���_�ݒ�

	// �ϐ��擾�E�ݒ�֐�
	D3DXVECTOR2 GetSize(void) { return D3DXVECTOR2(m_fWidth, m_fHeigth); }	// �T�C�Y
	void SetSize(float width, float height);
	float GetWidth(void) { return m_fWidth; }	// ��
	float GetHeight(void) { return m_fHeigth; }	// ����
	void SetAnim(int nAnim, int nNumAnim, int nNumV);	// �A�j���[�V����
	void SetTex(D3DXVECTOR2 texLeftUp, D3DXVECTOR2 texRightDown);	// �e�N�X�`�����W
	D3DXVECTOR3 GetPosition(void) { return m_pos; }	// �ʒu
	void SetPosition(D3DXVECTOR3 pos);
	void SetRot(float fRot);// �����ݒ菈��
	float GetRot(void) { return m_fRot; }	// �����擾����
	D3DXCOLOR GetCol(void) { return m_col; }	// �F
	void SetCol(D3DXCOLOR col);
	void SetIdxTexture(int nIdx) { m_nIdxTexture = nIdx; }	// �e�N�X�`���ԍ�
	int GetIdxTexture(void) { return m_nIdxTexture; }

	// �ÓI�����o�֐�
	static CObject2D *Create(int nPriority = 3);	// ��������

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXCOLOR m_col;	// �F
	float m_fRot;	// ����
	float m_fWidth;	// ��
	float m_fHeigth;	// ����
	int m_nIdxTexture;	// �e�N�X�`���̔ԍ�
};

#endif