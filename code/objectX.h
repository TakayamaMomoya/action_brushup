//*****************************************************
//
// X�t�@�C���̏���[objectX.h]
// Author:���R����
//
//*****************************************************
#ifndef _OBJECTX_H_	// ��d�C���N���[�h�h�~
#define _OBJECTX_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"
#include "model.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define NUM_TEX	(5)	// �e�N�X�`���̐�

//*****************************************************
// �N���X��`
//*****************************************************
class CObjectX : public CObject
{
public:
	CObjectX(int nPriority = 3);	// �R���X�g���N�^
	~CObjectX();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��
	void JustDraw(void);	// �`��݂̂��s��
	void CalcMatrix(void);	// �}�g���b�N�X�v�Z
	void DrawShadow(void);	// �e�̕`��

	// �ϐ��擾�E�ݒ�֐�
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }	// �ʒu
	D3DXVECTOR3 GetPosition(void) { return m_pos; }	// �擾����
	void SetPositionOld(D3DXVECTOR3 pos) { m_posOld = pos; }	// �O��̈ʒu
	D3DXVECTOR3 GetPositionOld(void) { return m_posOld; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }	// �ړ���
	D3DXVECTOR3 GetMove(void) { return m_move; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }	// ����
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	void BindModel(int nIdx);	// ���f���̊��蓖��
	int GetIdxModel(void) { return m_nIdxModel; }	// ���f���ԍ�
	void SetRadius(void);	// ���a
	float GetRadius(void) { return m_fRadius; }
	D3DXMATRIX *GetMatrix(void) { return &m_mtxWorld; }	// �}�g���b�N�X
	void SetMatrix(D3DXMATRIX mtx) { m_mtxWorld = mtx; }
	D3DXVECTOR3 GetVtxMax(void) { return m_vtxMax; }	// �ő咸�_
	D3DXVECTOR3 GetVtxMin(void) { return m_vtxMin; }	// �ŏ����_
	void SetEmissiveCol(D3DXCOLOR col) { m_col = col; m_bChangeCol = true; }	// �F
	D3DXCOLOR GetEmissiveCol(void);
	void ResetColor(void) { m_bChangeCol = false; }
	float GetScale(void) { return m_fScale; }	// �X�P�[��
	void SetScale(float fScale) { m_fScale = fScale; }
	CModel::Model *GetModel(void) { return m_pModel; }	// ���f�����
	void SetModel(CModel::Model *pModel) { m_pModel = pModel; }

	// �ÓI�����o�֐�
	static CObjectX *Create(D3DXVECTOR3 pos = { 0.0f,0.0f,0.0f }, D3DXVECTOR3 rot = { 0.0f,0.0f,0.0f });	// ��������

private:
	// �����o�ϐ�	
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_posOld;	// �O��̈ʒu
	D3DXVECTOR3 m_move;	// �ړ���
	D3DXVECTOR3 m_rot;	//����
	D3DXMATRIX m_mtxWorld;	//���[���h�}�g���b�N�X
	D3DXMATRIX m_mtxRot;	// ��]�}�g���b�N�X�ۑ��p
	D3DXVECTOR3 m_vecAxis;	// ��]��
	D3DXCOLOR m_col;	// �F
	CModel::Model *m_pModel;	// ���f�����
	int m_nIdxModel;	// ���f���̔ԍ�
	float m_fRadius;	// ���f���̔��a
	float m_fScale;	// �X�P�[��
	D3DXVECTOR3 m_vtxMax;	// �ő咸�_
	D3DXVECTOR3 m_vtxMin;	// �ŏ����_
	bool m_bChangeCol;	// �F�ύX�t���O
};

#endif