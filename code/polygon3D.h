//*****************************************************
//
// 3D�|���S���̏���[polygon3D.h]
// Author:���R����
//
//*****************************************************
#ifndef _POLYGON3D_H_	// ��d�C���N���[�h�h�~
#define _POLYGON3D_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CPolygon3D : public CObject
{
public:
	// �񋓌^��`
	enum E_MODE
	{// �`�惂�[�h
		MODE_NORMAL = 0,	// �ʏ탂�[�h
		MODE_BILLBOARD,	// �r���{�[�h
		MODE_STRETCHBILLBOARD,	// �X�g���b�`�r���{�[�h
		MODE_MAX
	};

	CPolygon3D(int nPriority = 2);	// �R���X�g���N�^
	~CPolygon3D();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��
	virtual void SetVtx(void);	// ���_�ݒ�

	// �ϐ��擾�E�ݒ�֐�
	float GetWidth(void) { return m_width; }	// ��
	float GetHeight(void) { return m_heigth; }	// ��
	void SetSize(float width, float height);	// �T�C�Y
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }	// �ʒu
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetPositionOld(void) { return m_posOld; }	// �O��̈ʒu
	D3DXVECTOR3 GetRotation(void) { return m_rot; }	// ����
	void SetRotation(D3DXVECTOR3 rot = { D3DX_PI * 0.5f,0.0f,0.0f }) { m_rot = rot; }
	void SetIdxTexture(int nIdx) { m_nIdxTexture = nIdx; }	// �e�N�X�`���ԍ�
	int GetIdxTexture(void) { return m_nIdxTexture; }
	D3DXCOLOR GetColor(void) { return m_col; }	// �F
	void SetColor(D3DXCOLOR col);
	void SetTex(D3DXVECTOR2 rd, D3DXVECTOR2 lu);	// �e�N�X�`���ԍ�
	void SetFactSB(float fFact) { m_fFactSB = fFact; }	// �X�g���b�`�r���{�[�h�̕␳�l
	void SetMode(E_MODE mode);	// �`�惂�[�h
	E_MODE GetMode(void) { return m_mode; }
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) { return m_pVtxBuff; }	// ���_�o�b�t�@
	D3DXMATRIX *GetMatrix(void) { return &m_mtxWorld; }	// �}�g���b�N�X

	// �ÓI�����o�֐�
	static CPolygon3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot = { 0.0f,0.0f,0.0f });	// ��������

private:
	// �����o�֐�
	void SetVtxNormal(void);	// �ʏ�̖@���ݒ�
	void SetVtxStretchBillboard(void);	// �X�g���b�`�r���{�[�h�̒��_�ݒ�
	void SetMtx(void);	// �}�g���b�N�X�ݒ�
	void SetMtxBillboard(void);	// �r���{�[�h�̃}�g���b�N�X�ݒ�

	// �����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_posOld;	// �O��̈ʒu
	D3DXVECTOR3 m_rot;	//����
	D3DXMATRIX m_mtxWorld;	//���[���h�}�g���b�N�X
	D3DXCOLOR m_col;	// �F
	float m_width;	// ��
	float m_heigth;	// ����
	float m_fFactSB;	// �X�g���b�`�r���{�[�h�̂Ƃ��̌��₷���̕␳
	int m_nIdxTexture;	// �e�N�X�`���̔ԍ�
	E_MODE m_mode;	// ���[�h
};

#endif