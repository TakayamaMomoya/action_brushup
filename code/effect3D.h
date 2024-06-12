//*****************************************************
//
// 3D�G�t�F�N�g����[effect3D.h]
// Author:���R����
//
//*****************************************************
#ifndef _EFFECT3D_H_	// ��d�C���N���[�h�h�~
#define _EFFECT3D_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "billboard.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CEffect3D : public CBillboard
{
public:
	CEffect3D(int nPriority = 6);	// �R���X�g���N�^
	~CEffect3D();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void); // ������
	void Uninit(void);  // �I��
	void Update(void);  // �X�V
	void Draw(void);  // �`��

	// �ÓI�����o�֐�
	// ��������
	static CEffect3D *Create(D3DXVECTOR3 pos, float fRadius, int nLife, D3DXCOLOR col, D3DXVECTOR3 move = { 0.0f,0.0f,0.0f },
		float fGravity = 0.0f, bool bAdd = true, float fDecrease = 0.0f, D3DXVECTOR3 *pPosOwner = nullptr, int nPriority = 6, bool bTurn = false);

private:
	// �����o�ϐ�
	int m_nLife;	// ����
	float m_fDecreaseRadius;	// ���a������
	float m_fDecreaseAlpha;	// ���l������
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_relPos;	// ���Έʒu
	D3DXVECTOR3 *m_pPosOwner;	// ������̃|�C���^
	bool m_bAdd;	// ���Z����
	float m_fGravity;	// �d��
};

#endif