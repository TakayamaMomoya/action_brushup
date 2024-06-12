//*****************************************************
//
// 2D�G�t�F�N�g����[effect2D.h]
// Author:���R����
//
//*****************************************************
#ifndef _EFFECT2D_H_	// ��d�C���N���[�h�h�~
#define _EFFECT2D_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "Object2D.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CEffect2D : public CObject2D
{
public:
	CEffect2D(int nPriority = 5);	// �R���X�g���N�^
	~CEffect2D();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void); // ������
	void Uninit(void);  // �I��
	void Update(void);  // �X�V
	void Draw(void);  // �`��

	// �ϐ��擾�E�ݒ�֐�
	D3DXVECTOR3 GetMove(void) { return m_move; }	// �ړ���
	void SetMove(D3DXVECTOR3 move) { m_move = move; }

	// �ÓI�����o�֐�
	static CEffect2D *Create(D3DXVECTOR3 pos, float fRadius, int nLife, D3DXCOLOR col, D3DXVECTOR3 move = { 0.0f,0.0f,0.0f });

private:
	// �����o�ϐ�
	int m_nLife;	// ����
	float m_fDecrease;	// ������
	D3DXVECTOR3 m_move;	// �ړ���
};

#endif