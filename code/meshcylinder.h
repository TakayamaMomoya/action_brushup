//*****************************************************
//
// ���b�V���V�����_�[�̏���[meshcylinder.h]
// Author:���R����
//
//*****************************************************

#ifndef _MESHCYLINDER_H_
#define _MESHCYLINDER_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �N���X��`
//*****************************************************
class CMeshCylinder : public CObject
{
public:
	CMeshCylinder(int nPriority = 5);	// �R���X�g���N�^
	~CMeshCylinder();	// �f�X�g���N�^

	typedef struct
	{
		D3DXVECTOR3 pos;						//�ʒu
		D3DXVECTOR3 rot;						//����
		D3DXMATRIX mtxWorld;					//���[���h�}�g���b�N�X
		int nNumIdx;							//�C���f�b�N�X��
		int nNumVtx;							//���_��
	}MeshCylinder;

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMeshCylinder *Create(void);
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) { return m_pVtxBuff; }
	void SetPosition(D3DXVECTOR3 pos) { m_meshCylinder.pos = pos; }
	D3DXVECTOR3 GetPosition(void) { return m_meshCylinder.pos; }
	int GetNumVtx(void) { return m_meshCylinder.nNumVtx; }

private:
	LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	MeshCylinder m_meshCylinder;	//�\���̂̏��
	D3DXCOLOR m_col;	// �F
};
#endif